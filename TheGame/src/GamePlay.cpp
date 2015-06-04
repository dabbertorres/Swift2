#include "GamePlay.hpp"

#include "GameMenu.hpp"
#include "GameSettingsMenu.hpp"

#include "GameScript.hpp"

#include "Logger/Logger.hpp"

#include "GUI/Containers/Column.hpp"
#include "GUI/Containers/Row.hpp"
#include "GUI/Widgets/Label.hpp"
#include "GUI/Widgets/Button.hpp"
#include "GUI/Widgets/Spacer.hpp"

#include <tinyxml2.h>

namespace tg
{
	const float MAX_ZOOM = 2.f;
	const float MIN_ZOOM = 0.5f;

	GamePlay::GamePlay(sf::RenderWindow& win, GameAssets& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::StateMachine& sm)
	:	GameState(win, am, sp, mp, set, sm),
		activeState(nullptr),
		activeWorld(nullptr),
		playView({0, 0}, {static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y)})
	{
		GameScript::setPlayState(*this);

		setupSubStates();

		//loadLastWorld();

		window.setKeyRepeatEnabled(false);

		setupKeyBindings();
		setupGUI();

		// set the active state
		activeState = &play;
	}

	GamePlay::~GamePlay()
	{
		for(auto & w : worlds)
		{
			saveWorld(*w.second);
			delete w.second;
		}
	}

	void GamePlay::handleEvent(const sf::Event& event)
	{
		if(event.type == sf::Event::Resized)
		{
			playView.setSize(event.size.width, event.size.height);
		}

		activeState->handleEvents(event);

		keyboard(event);
		mouse(event);
	}

	void GamePlay::update(const sf::Time& dt)
	{
		activeState->update(dt);

		soundPlayer.update();
		musicPlayer.update();
	}

	void GamePlay::draw()
	{
		activeState->draw();
	}

	unsigned int GamePlay::getPlayer() const
	{
		return activeWorld->getPlayer();
	}

	void GamePlay::changeWorld(const std::string& name, const std::string& mapFile)
	{
		worlds.emplace(name, new GameWorld(name, &assets));
		GameWorld* newWorld = worlds[name];

		// setup world
		bool mapResult = newWorld->tilemap.loadFile(mapFile);
		bool textureResult = newWorld->tilemap.loadTexture(*assets.getTexture(newWorld->tilemap.getTextureFile()));

		if(!mapResult)
		{
			swift::Logger::get() << "[ERROR]: Loading tilemap \"" << mapFile << "\" failed.\n";
		}

		if(!textureResult)
		{
			swift::Logger::get() << "[ERROR]: Setting texture for \"" << mapFile << "\" failed.\n";
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
			// copy over player from current world to new world
			unsigned int oldPlayer = activeWorld->getPlayer();
			newWorld->createEntity(oldPlayer);
			
			// create and copy components from oldPlayer to new Player

			// delete old world
			std::string oldWorld = activeWorld->getName();
			saveWorld(*activeWorld);
			delete activeWorld;
			worlds.erase(oldWorld);

			// load the world's save file
			if(!loadWorld(*newWorld))
			{
				swift::Logger::get() << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
			}
		}
		else
		{
			// load the world's save file
			if(!loadWorld(*newWorld))
			{
				swift::Logger::get() << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
			}
		}

		activeWorld = newWorld;
		GameScript::setWorld(*activeWorld);
	}

	void GamePlay::loadLastWorld()
	{
		//changeWorld(worldName, tilemapFile);
	}

	bool GamePlay::loadWorld(swift::World& world)
	{
		std::string file = "../data/saves/" + world.getName() + ".world";

		tinyxml2::XMLDocument loadFile;
		loadFile.LoadFile(file.c_str());

		if(loadFile.Error())
		{
			swift::Logger::get() << "[ERROR]: Loading world save file \"" << file << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* worldRoot = loadFile.FirstChildElement("world");

		if(worldRoot == nullptr)
		{
			swift::Logger::get() << "[ERROR]: World save file \"" << file << "\" does not have a \"world\" root element.\n";
			return false;
		}

		tinyxml2::XMLElement* entityElement = worldRoot->FirstChildElement("entity");

		while(entityElement != nullptr)
		{
			//unsigned int entity = world.createEntity(0);

			tinyxml2::XMLElement* component = entityElement->FirstChildElement();

			while(component != nullptr)
			{
				std::string componentName = component->Value();
				//entity->add(componentName);

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
				//entity->get(componentName)->unserialize(variables);

				if(componentName == "Drawable")
				{
					/*swift::Drawable* draw = entity->get<swift::Drawable>();
					draw->sprite.setTexture(*assets.getTexture(draw->texture));*/
				}
				else if(componentName == "Animated")
				{
					/*swift::Animated* anim = entity->get<swift::Animated>();
					anim->animTex = assets.getAnimTexture(anim->animationFile);
					anim->createAnimations();
					anim->sprite.setTexture(*assets.getTexture(anim->animTex->getTextureFile()));
					anim->currentAnim = "Idle";
					anim->previousAnim = "Idle";
					anim->setAnimation("Idle");*/
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
			swift::Logger::get() << "[ERROR]: Saving world save file \"" << file << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* root = saveFile.FirstChildElement("world");

		if(root == nullptr)
		{
			swift::Logger::get() << "[WARNING]: World save file \"" << file << "\" does not have a \"world\" root element.\n";
			root = saveFile.NewElement("world");
			saveFile.InsertFirstChild(root);
		}
		else
		{
			root->DeleteChildren();
		}

		/*for(auto & e : world.getEntities())
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
		}*/

		saveFile.SaveFile(file.c_str());

		return true;
	}

	void GamePlay::setupGUI()
	{
		auto* font = assets.getFont("segoeuisl.ttf");
		auto* buttonTexture = assets.getTexture("button.png");
		
		std::string dictStr = "en";
		
		if(!settings.get("lang", dictStr))
		{
			swift::Logger::get() << "[WARNING]: No language set, defaulting to English (en).\n";
		}
		
		swift::Dictionary* dictionary = assets.getDict(dictStr);

		if(!font)
		{
			swift::Logger::get() << "[ERROR]: Could not find segoeuisl.ttf!\n";
			return;
		}

		if(!buttonTexture)
		{
			swift::Logger::get() << "[ERROR]: Could not find button.png!\n";
			return;
		}
		
		if(!dictionary)
		{
			swift::Logger::get() << "[WARNING]: Could not find dictionary for: \"" << dictStr << "\", defaulting to English (en).\n";
		}
		
		// setup pause menu GUI
		cstr::Column& pauseColumn = pauseMenu.addContainer(new cstr::Column({static_cast<int>(window.getSize().x) / 2 - 50, static_cast<int>(window.getSize().y / 2) - 50, 100, 200}, false));
		
		// resume button
		std::string resume = "Resume";
		dictionary->get("resumeButton", resume);
		pauseColumn.addWidget(new cstr::Button({100, 50}, *buttonTexture, [&]()
		{
			activeState = &play;
		})).setString(resume, *font, 25);

		pauseColumn.addWidget(new cstr::Spacer({100, 25}));
		
		// settings menu button
		std::string settingsMenu = "Settings";
		dictionary->get("settingsButton", settingsMenu);
		pauseColumn.addWidget(new cstr::Button({100, 50}, *buttonTexture, [&]()
		{
			states.push(new GameSettingsMenu(window, assets, soundPlayer, musicPlayer, settings, states), false);
		})).setString(settingsMenu, *font, 25);

		pauseColumn.addWidget(new cstr::Spacer({100, 25}));
		
		// main menu (exit) button
		std::string mainMenu = "Main Menu";
		dictionary->get("mainMenuButton", mainMenu);
		pauseColumn.addWidget(new cstr::Button({100, 50}, *buttonTexture, [&]()
		{
			done = true;
			states.push(new GameMenu(window, assets, soundPlayer, musicPlayer, settings, states));
		})).setString(mainMenu, *font, 20);
	}

	void GamePlay::setupSubStates()
	{
		// setup SubStates
		play.setEventFunc([&](const sf::Event& e)
		{
			hud.update(e);

			switch(e.type)
			{
				case sf::Event::LostFocus:
					/*if(player)
						if(player->has<swift::Movable>())
							player->get<swift::Movable>()->velocity = {0, 0};*/

					break;

				default:
					break;
			}
		});

		play.setUpdateFunc([&](const sf::Time& dt)
		{
			//activeWorld->update(dt.asSeconds());
			
			/*if(player)
			{
				playView.setCenter(std::floor(player->get<swift::Physical>()->position.x), std::floor(player->get<swift::Physical>()->position.y));
				soundPlayer.setListenerPosition({player->get<swift::Physical>()->position.x, player->get<swift::Physical>()->position.y, 0});

				swift::Controllable* cont = player->get<swift::Controllable>();

				if(!cont->moveUp && !cont->moveDown && !cont->moveLeft && !cont->moveRight)
				{
					player->get<swift::Animated>()->setAnimation("Idle");
				}
			}
			else
			{
				playView.setCenter(0, 0);
				soundPlayer.setListenerPosition({0, 0, 0});
			}*/
		});

		play.setDrawFunc([&]()
		{
			window.setView(playView);
			//activeWorld->draw(window);

			window.setView(window.getDefaultView());
			window.draw(hud);
		});

		pause.setEventFunc([&](const sf::Event& e)
		{
			pauseMenu.update(e);
		});

		pause.setDrawFunc([&]()
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
			/*if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveUp = true;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->setAnimation("WalkVert");
				}
			}*/
		}, true);

		keyboard.newBinding("moveUpStop", sf::Keyboard::Up, [&]()
		{
			/*if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveUp = false;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->revertAnimation();
				}
			}*/
		}, false);

		// move down press and release
		keyboard.newBinding("moveDownStart", sf::Keyboard::Down, [&]()
		{
			/*if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveDown = true;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->setAnimation("WalkVert");
				}
			}*/
		}, true);

		keyboard.newBinding("moveDownStop", sf::Keyboard::Down, [&]()
		{
			/*if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveDown = false;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->revertAnimation();
				}
			}*/
		}, false);

		// move left press and release
		keyboard.newBinding("moveLeftStart", sf::Keyboard::Left, [&]()
		{
			/*if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveLeft = true;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->setAnimation("WalkLeft");
				}
			}*/
		}, true);

		keyboard.newBinding("moveLeftStop", sf::Keyboard::Left, [&]()
		{
			/*if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveLeft = false;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->revertAnimation();
				}
			}*/
		}, false);

		// move right press and release
		keyboard.newBinding("moveRightStart", sf::Keyboard::Right, [&]()
		{
		/*	if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveRight = true;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->setAnimation("WalkRight");
				}
			}*/
		}, true);

		keyboard.newBinding("moveRightStop", sf::Keyboard::Right, [&]()
		{
			/*if(player)
			{
				if(player->has<swift::Controllable>())
				{
					player->get<swift::Controllable>()->moveRight = false;
				}

				if(player->has<swift::Animated>())
				{
					player->get<swift::Animated>()->revertAnimation();
				}
			}*/
		}, false);
	}
}
