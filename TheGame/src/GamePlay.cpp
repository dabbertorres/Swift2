#include "GamePlay.hpp"

#include "GameMenu.hpp"

#include "GameScript.hpp"

#include "../src/Logger/Logger.hpp"

/* GUI headers */
#include "../src/GUI/Containers/Column.hpp"
#include "../src/GUI/Containers/Row.hpp"
#include "../src/GUI/Widgets/Label.hpp"
#include "../src/GUI/Widgets/Button.hpp"
#include "../src/GUI/Widgets/Spacer.hpp"

namespace tg
{
	const float MAX_ZOOM = 2.f;
	const float MIN_ZOOM = 0.5f;

	GamePlay::GamePlay(sf::RenderWindow& win, swift::AssetManager& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic, swift::StateMachine& sm)
	:	State(win, am, sp, mp, set, dic, sm),
		activeState(nullptr),
		activeWorld(nullptr),
		player(nullptr)
	{
		GameScript::setPlayState(*this);
		
		setupSubStates();
		
		loadLastWorld();

		window.setKeyRepeatEnabled(false);

		setupKeyBindings();
		setupGUI();
		
		swift::Animated* anim = player->get<swift::Animated>();
		anim->animTex = assets.getAnimTexture(anim->animationFile);
		anim->sprite.setTexture(*assets.getTexture(anim->animTex->getTextureFile()));
		anim->currentAnim = "Idle";
		anim->previousAnim = "Idle";
		anim->anims["Idle"] = anim->animTex->getAnimFrames("Idle");
		anim->anims["WalkVert"] = anim->animTex->getAnimFrames("WalkVert");
		anim->anims["WalkRight"] = anim->animTex->getAnimFrames("WalkRight");
		anim->anims["WalkLeft"] = anim->animTex->getAnimFrames("WalkLeft");

		// set the active state
		activeState = &play;
	}
	
	GamePlay::~GamePlay()
	{
		std::ofstream fout;
		
		fout.open("./data/saves/currentWorld");
		fout << activeWorld->getName() << '\n';
		fout << activeWorld->tilemap.getFile() << '\n';
		fout.close();
		
		for(auto& w : worlds)
			delete w.second;

		for(auto& s : scripts)
			removeScript(s.first);
	}
	
	void GamePlay::handleEvent(sf::Event& event)
	{
		activeState->handleEvents(event);

		keyboard(event);
		mouse(event);
	}
	
	void GamePlay::update(sf::Time dt)
	{
		activeState->update(dt);

		soundPlayer.update();
		musicPlayer.update();
		
		updateScripts();
	}
	
	void GamePlay::draw(float e)
	{
		activeState->draw(e);
	}

	bool GamePlay::addScript(const std::string& scriptFile)
	{
		if(scripts.find(scriptFile) == scripts.end())
		{
			scripts.emplace(scriptFile, assets.getScript(scriptFile));
			scripts[scriptFile]->start();
			return true;
		}
		else
			return false;
	}

	bool GamePlay::removeScript(const std::string& scriptFile)
	{
		if(scripts.find(scriptFile) != scripts.end())
		{
			if(!scripts[scriptFile]->save("./data/saves/" + scriptFile.substr(scriptFile.find_last_of('/') + 1) + ".script"))
				swift::log << "[WARNING]: Could not save script: " << scriptFile << "!\n";
			scripts[scriptFile]->reset();
			scripts.erase(scriptFile);
			return true;
		}
		else
			return false;
	}

	swift::Entity* GamePlay::getPlayer() const
	{
		return player;
	}

	void GamePlay::changeWorld(const std::string& name, const std::string& mapFile)
	{
		worlds.emplace(name, new swift::World(name, assets, soundPlayer, musicPlayer, {}));
		swift::World* newWorld = worlds[name];

		// setup world
		bool mapResult = newWorld->tilemap.loadFile(mapFile);
		bool textureResult = newWorld->tilemap.loadTexture(*assets.getTexture(newWorld->tilemap.getTextureFile()));

		if(!mapResult)
			swift::log << "[ERROR]: Loading tilemap \"" << mapFile << "\" failed.\n";

		if(!textureResult)
			swift::log << "[ERROR]: Setting texture for \"" << mapFile << "\" failed.\n";

		if(!mapResult || !textureResult)
		{
			worlds.erase(name);	// undo what we did and exit since loading the world failed
			return;
		}

		// get the player
		if(activeWorld)
		{
			// copy over play from current world to new world
			swift::Entity* newPlayer = newWorld->addEntity();
			*newPlayer = *player;
			player = newPlayer;

			activeWorld->removeEntity(0);	// delete player from current world

			// delete old world
			std::string oldWorld = activeWorld->getName();
			delete activeWorld;
			worlds.erase(oldWorld);

			// load the world's save file
			bool loadResult = newWorld->load();
			
			if(!loadResult)
				swift::log << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
		}
		else
		{
			// load the world's save file
			bool loadResult = newWorld->load();
			
			if(!loadResult)
				swift::log << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
			
			for(auto& e : newWorld->getEntities())
			{
				if(e->has<swift::Controllable>())
				{
					player = e;
					break;
				}
			}
		}

		activeWorld = newWorld;
		GameScript::setWorld(*activeWorld);
	}
	
	void GamePlay::loadLastWorld()
	{
		std::ifstream fin;
		
		std::string worldName;
		std::string tilemapFile;
		
		fin.open("./data/saves/currentWorld");
		std::getline(fin, worldName);
		std::getline(fin, tilemapFile);
		fin.close();

		// create worlds
		changeWorld(worldName, tilemapFile);
	}
	
	void GamePlay::updateScripts()
	{
		std::vector<std::string> doneScripts;

		for(auto& s : scripts)
		{
			s.second->update();

			// check if script is done, if so, push it for deletion
			if(s.second->toDelete())
				doneScripts.push_back(s.first);
		}

		// remove all done scripts
		for(auto& s : doneScripts)
		{
			removeScript(s);
		}
	}
	
	void GamePlay::setupGUI()
	{
		// setup pause menu GUI
		std::string resume = "Resume";
		dictionary.get("resumeButton", resume);
		cstr::Column& pauseColumn = pauseMenu.addContainer(new cstr::Column( {static_cast<int>(window.getSize().x) / 2 - 50, static_cast<int>(window.getSize().y / 2) - 50, 100, 125}, false));
		pauseColumn.addWidget(new cstr::Button( {100, 50}, *assets.getTexture("./data/textures/button.png"), [&]()
		{
			activeState = &play;
		})).setString(resume, *assets.getFont("./data/fonts/segoeuisl.ttf"), 25);

		pauseColumn.addWidget(new cstr::Spacer( {100, 25}));

		std::string mainMenu = "Main Menu";
		dictionary.get("mainMenuButton", mainMenu);
		pauseColumn.addWidget(new cstr::Button( {100, 50}, *assets.getTexture("./data/textures/button.png"), [&]()
		{
			shouldReturn = true;
			states.push(new GameMenu(window, assets, soundPlayer, musicPlayer, settings, dictionary, states));
		})).setString(mainMenu, *assets.getFont("./data/fonts/segoeuisl.ttf"), 20);
	}
	
	void GamePlay::setupSubStates()
	{
		// setup SubStates
		play.setEventFunc([&](sf::Event& e)
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
				soundPlayer.setListenerPosition({player->get<swift::Physical>()->position.x, player->get<swift::Physical>()->position.y, 0});
			}
			else
			{
				playView.setCenter(0, 0);
				soundPlayer.setListenerPosition({0, 0, 0});
			}
		});

		play.setDrawFunc([&](float e)
		{
			window.setView(playView);
			activeWorld->drawWorld(window);
			activeWorld->drawEntities(window, e);

			window.setView(window.getDefaultView());
			window.draw(hud);
		});

		pause.setEventFunc([&](sf::Event& e)
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
					player->get<swift::Controllable>()->moveUp = true;
				
				if(player->has<swift::Animated>())
					player->get<swift::Animated>()->setAnimation("WalkVert");
			}
		}, true);

		keyboard.newBinding("moveUpStop", sf::Keyboard::Up, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
					player->get<swift::Controllable>()->moveUp = false;
				
				if(player->has<swift::Animated>())
					player->get<swift::Animated>()->revertAnimation();
			}
		}, false);

		// move down press and release
		keyboard.newBinding("moveDownStart", sf::Keyboard::Down, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
					player->get<swift::Controllable>()->moveDown = true;
				
				if(player->has<swift::Animated>())
					player->get<swift::Animated>()->setAnimation("WalkVert");
			}
					
		}, true);

		keyboard.newBinding("moveDownStop", sf::Keyboard::Down, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
					player->get<swift::Controllable>()->moveDown = false;
				
				if(player->has<swift::Animated>())
					player->get<swift::Animated>()->revertAnimation();
			}
		}, false);

		// move left press and release
		keyboard.newBinding("moveLeftStart", sf::Keyboard::Left, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
					player->get<swift::Controllable>()->moveLeft = true;
				
				if(player->has<swift::Animated>())
					player->get<swift::Animated>()->setAnimation("WalkLeft");
			}
		}, true);

		keyboard.newBinding("moveLeftStop", sf::Keyboard::Left, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
					player->get<swift::Controllable>()->moveLeft = false;
				
				if(player->has<swift::Animated>())
					player->get<swift::Animated>()->revertAnimation();
			}
		}, false);

		// move right press and release
		keyboard.newBinding("moveRightStart", sf::Keyboard::Right, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
					player->get<swift::Controllable>()->moveRight = true;
				
				if(player->has<swift::Animated>())
					player->get<swift::Animated>()->setAnimation("WalkRight");
			}
		}, true);

		keyboard.newBinding("moveRightStop", sf::Keyboard::Right, [&]()
		{
			if(player)
			{
				if(player->has<swift::Controllable>())
					player->get<swift::Controllable>()->moveRight = false;
					
				if(player->has<swift::Animated>())
					player->get<swift::Animated>()->revertAnimation();
			}
		}, false);
	}
}
