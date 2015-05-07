#include "GamePlay.hpp"

#include "GameMenu.hpp"

#include "GameScript.hpp"

#include "../../src/ResourceManager/AssetManager.hpp"

#include "../src/Logger/Logger.hpp"

/* GUI headers */
#include "../src/GUI/Containers/Column.hpp"
#include "../src/GUI/Containers/Row.hpp"
#include "../src/GUI/Widgets/Label.hpp"
#include "../src/GUI/Widgets/Button.hpp"
#include "../src/GUI/Widgets/Spacer.hpp"

#include <tinyxml2.h>

namespace tg
{
	const float MAX_ZOOM = 2.f;
	const float MIN_ZOOM = 0.5f;

	GamePlay::GamePlay(sf::RenderWindow& win, swift::AssetManager& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set,
	                   swift::Settings& dic, swift::StateMachine& sm, const std::string& rp)
		:	State(win, am, sp, mp, set, dic, sm, rp),
		    activeState(nullptr),
		    activeWorld(nullptr),
		    player(nullptr),
		playView( {0, 0}, {static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y)}),
	scripts(am)
	{
		GameScript::setPlayState(*this);

		setupSubStates();

		loadLastWorld();

		window.setKeyRepeatEnabled(false);

		setupKeyBindings();
		setupGUI();

		// set the active state
		activeState = &play;
	}

	GamePlay::~GamePlay()
	{
		std::ofstream fout;

		fout.open(resPath + "../data/saves/currentWorld");
		fout << activeWorld->getName() << '\n';
		fout << activeWorld->tilemap.getFile() << '\n';
		fout.close();

		for(auto & w : worlds)
		{
			saveWorld(*w.second);
			delete w.second;
		}

		scripts.removeAll();
	}

	void GamePlay::handleEvent(sf::Event& event)
	{
		if(event.type == sf::Event::Resized)
		{
			playView.setSize(event.size.width, event.size.height);
		}

		activeState->handleEvents(event);

		keyboard(event);
		mouse(event);
	}

	void GamePlay::update(sf::Time dt)
	{
		activeState->update(dt);

		soundPlayer.update();
		musicPlayer.update();

		scripts.update();
	}

	void GamePlay::draw(float e)
	{
		activeState->draw(e);
	}

	swift::Entity* GamePlay::getPlayer() const
	{
		return activeWorld->getPlayer();
	}

	void GamePlay::changeWorld(const std::string& name, const std::string& mapFile)
	{
		worlds.emplace(name, new GameWorld(name, assets));
		GameWorld* newWorld = worlds[name];

		// setup world
		bool mapResult = newWorld->tilemap.loadFile(mapFile);
		bool textureResult = newWorld->tilemap.loadTexture(*assets.getTexture(newWorld->tilemap.getTextureFile()));

		if(!mapResult)
		{
			swift::log << "[ERROR]: Loading tilemap \"" << mapFile << "\" failed.\n";
		}

		if(!textureResult)
		{
			swift::log << "[ERROR]: Setting texture for \"" << mapFile << "\" failed.\n";
		}

		if(!mapResult || !textureResult)
		{
			delete worlds[name];
			worlds.erase(name);	// undo what we did and exit since loading the world failed
			return;
		}

		// get the player
		if(activeWorld)
		{
			// copy over play from current world to new world
			swift::Entity* newPlayer = newWorld->addEntity();
			*newPlayer = *activeWorld->getPlayer();
			player = newPlayer;

			activeWorld->removeEntity(0);	// delete player from current world

			// delete old world
			std::string oldWorld = activeWorld->getName();
			saveWorld(*activeWorld);
			delete activeWorld;
			worlds.erase(oldWorld);

			// load the world's save file
			if(!loadWorld(*newWorld))
			{
				swift::log << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
			}
		}
		else
		{
			// load the world's save file
			if(!loadWorld(*newWorld))
			{
				swift::log << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
			}

			player = newWorld->getPlayer();
		}

		activeWorld = newWorld;
		GameScript::setWorld(*activeWorld);
	}

	void GamePlay::loadLastWorld()
	{
		std::ifstream fin;

		std::string worldName;
		std::string tilemapFile;

		fin.open(resPath + "../data/saves/currentWorld");

		if(fin.good())
		{
			std::getline(fin, worldName);
			std::getline(fin, tilemapFile);

			// create world
			changeWorld(worldName, tilemapFile);
		}
		else
		{
			swift::log << "[WARNING]: No current world set!\n";
			changeWorld("simple", resPath + "../data/maps/simple.tmx");
		}

		fin.close();
	}

	bool GamePlay::loadWorld(swift::World& world)
	{
		std::string file = "../data/saves/" + world.getName() + ".world";

		tinyxml2::XMLDocument loadFile;
		loadFile.LoadFile(file.c_str());

		if(loadFile.Error())
		{
			swift::log << "[ERROR]: Loading world save file \"" << file << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* worldRoot = loadFile.FirstChildElement("world");

		if(worldRoot == nullptr)
		{
			swift::log << "[ERROR]: World save file \"" << file << "\" does not have a \"world\" root element.\n";
			return false;
		}

		tinyxml2::XMLElement* entityElement = worldRoot->FirstChildElement("entity");

		while(entityElement != nullptr)
		{
			swift::Entity* entity = world.addEntity();

			tinyxml2::XMLElement* component = entityElement->FirstChildElement();

			while(component != nullptr)
			{
				std::string componentName = component->Value();
				entity->add(componentName);

				std::map<std::string, std::string> variables;
				tinyxml2::XMLElement* variableElement = component->FirstChildElement();

				while(variableElement != nullptr)
				{
					// make sure the strings aren't empty...
					if(std::string(variableElement->Value()).size() > 0 && std::string(variableElement->GetText()).size() > 0)
					{
						variables.emplace(variableElement->Value(), variableElement->GetText());
					}

					variableElement = variableElement->NextSiblingElement();
				}

				// get component and add to it
				entity->get(componentName)->unserialize(variables);

				if(componentName == "Drawable")
				{
					swift::Drawable* draw = entity->get<swift::Drawable>();
					draw->sprite.setTexture(*assets.getTexture(draw->texture));
				}
				else if(componentName == "Animated")
				{
					swift::Animated* anim = entity->get<swift::Animated>();
					anim->animTex = assets.getAnimTexture(anim->animationFile);
					anim->createAnimations();
					anim->sprite.setTexture(*assets.getTexture(anim->animTex->getTextureFile()));
					anim->currentAnim = "Idle";
					anim->previousAnim = "Idle";
					anim->setAnimation("Idle");
				}

				component = component->NextSiblingElement();
			}

			entityElement = entityElement->NextSiblingElement("entity");
		}

		return true;
	}

	bool GamePlay::saveWorld(swift::World& world)
	{
		std::string file = "../data/saves/" + world.getName() + ".world";

		tinyxml2::XMLDocument saveFile;
		tinyxml2::XMLError result = saveFile.LoadFile(file.c_str());

		if(result != tinyxml2::XML_SUCCESS && result != tinyxml2::XML_ERROR_EMPTY_DOCUMENT && result != tinyxml2::XML_ERROR_FILE_NOT_FOUND)
		{
			swift::log << "[ERROR]: Saving world save file \"" << file << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* root = saveFile.FirstChildElement("world");

		if(root == nullptr)
		{
			swift::log << "[WARNING]: World save file \"" << file << "\" does not have a \"world\" root element.\n";
			root = saveFile.NewElement("world");
			saveFile.InsertFirstChild(root);
		}
		else
		{
			root->DeleteChildren();
		}

		for(auto & e : world.getEntities())
		{
			tinyxml2::XMLElement* entity = saveFile.NewElement("entity");

			for(auto & c : e->getComponents())
			{
				tinyxml2::XMLElement* component = saveFile.NewElement(c.first.c_str());

				for(auto & v : c.second->serialize())
				{
					tinyxml2::XMLElement* variable = saveFile.NewElement(v.first.c_str());
					variable->SetText(v.second.c_str());
					component->InsertEndChild(variable);
				}

				entity->InsertEndChild(component);
			}

			root->InsertEndChild(entity);
		}

		saveFile.SaveFile(file.c_str());

		return true;
	}

	void GamePlay::setupGUI()
	{
		auto* font = assets.getFont("segoeuisl.ttf");
		auto* buttonTexture = assets.getTexture("button.png");

		if(!font)
		{
			swift::log << "[ERROR]: Could not find segoeuisl.ttf!\n";
			return;
		}

		if(!buttonTexture)
		{
			swift::log << "[ERROR]: Could not find button.png!\n";
			return;
		}

		// setup pause menu GUI
		std::string resume = "Resume";
		dictionary.get("resumeButton", resume);
		cstr::Column& pauseColumn = pauseMenu.addContainer(new cstr::Column( {static_cast<int>(window.getSize().x) / 2 - 50, static_cast<int>(window.getSize().y / 2) - 50, 100, 125}, false));
		pauseColumn.addWidget(new cstr::Button( {100, 50}, *buttonTexture, [&]()
		{
			activeState = &play;
		})).setString(resume, *font, 25);

		pauseColumn.addWidget(new cstr::Spacer( {100, 25}));

		std::string mainMenu = "Main Menu";
		dictionary.get("mainMenuButton", mainMenu);
		pauseColumn.addWidget(new cstr::Button( {100, 50}, *buttonTexture, [&]()
		{
			shouldReturn = true;
			states.push(new GameMenu(window, assets, soundPlayer, musicPlayer, settings, dictionary, states, resPath));
		})).setString(mainMenu, *font, 20);
	}

	void GamePlay::setupSubStates()
	{
		// setup SubStates
		play.setEventFunc([&](sf::Event & e)
		{
			hud.update(e);

			switch(e.type)
			{
				case sf::Event::LostFocus:
					if(player)
						if(player->has<swift::Movable>())
							player->get<swift::Movable>()->velocity = {0, 0};

					break;

				default:
					break;
			}
		});

		play.setUpdateFunc([&](sf::Time dt)
		{
			activeWorld->update(dt.asSeconds());

			if(player)
			{
				playView.setCenter(std::floor(player->get<swift::Physical>()->position.x), std::floor(player->get<swift::Physical>()->position.y));
				soundPlayer.setListenerPosition( {player->get<swift::Physical>()->position.x, player->get<swift::Physical>()->position.y, 0});

				swift::Controllable* cont = player->get<swift::Controllable>();

				if(!cont->moveUp && !cont->moveDown && !cont->moveLeft && !cont->moveRight)
				{
					player->get<swift::Animated>()->setAnimation("Idle");
				}
			}
			else
			{
				playView.setCenter(0, 0);
				soundPlayer.setListenerPosition( {0, 0, 0});
			}
		});

		play.setDrawFunc([&](float e)
		{
			window.setView(playView);
			activeWorld->draw(window, e);

			window.setView(window.getDefaultView());
			window.draw(hud);
		});

		pause.setEventFunc([&](sf::Event & e)
		{
			pauseMenu.update(e);
		});

		pause.setUpdateFunc([&](sf::Time)
		{
			// do nothing
		});

		pause.setDrawFunc([&](float)
		{
			window.draw(pauseMenu);
		});
	}

	void GamePlay::setupKeyBindings()
	{
		keyboard.newBinding("PauseMenu", sf::Keyboard::Escape, [&]()
		{
			activeState = (activeState == &pause) ? &play : &pause;
		}, false);

		// move up press and release
		keyboard.newBinding("moveUpStart", sf::Keyboard::Up, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveUp = true;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->setAnimation("WalkVert");
				}
			}
		}, true);

		keyboard.newBinding("moveUpStop", sf::Keyboard::Up, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveUp = false;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->revertAnimation();
				}
			}
		}, false);

		// move down press and release
		keyboard.newBinding("moveDownStart", sf::Keyboard::Down, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveDown = true;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->setAnimation("WalkVert");
				}
			}

		}, true);

		keyboard.newBinding("moveDownStop", sf::Keyboard::Down, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveDown = false;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->revertAnimation();
				}
			}
		}, false);

		// move left press and release
		keyboard.newBinding("moveLeftStart", sf::Keyboard::Left, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveLeft = true;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->setAnimation("WalkLeft");
				}
			}
		}, true);

		keyboard.newBinding("moveLeftStop", sf::Keyboard::Left, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveLeft = false;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->revertAnimation();
				}
			}
		}, false);

		// move right press and release
		keyboard.newBinding("moveRightStart", sf::Keyboard::Right, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveRight = true;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->setAnimation("WalkRight");
				}
			}
		}, true);

		keyboard.newBinding("moveRightStop", sf::Keyboard::Right, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveRight = false;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->revertAnimation();
				}
			}
		}, false);
	}
}
