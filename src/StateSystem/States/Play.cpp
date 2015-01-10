#include "Play.hpp"

#include <fstream>

#include "../../ResourceManager/AssetManager.hpp"

/* GUI headers */
#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Spacer.hpp"

/* SoundSystem headers */
#include "../../SoundSystem/SoundPlayer.hpp"
#include "../../SoundSystem/MusicPlayer.hpp"

/* EntitySystem headers */
#include "../../EntitySystem/Components/Pathfinder.hpp"

/* Pathfinding headers */
#include "../../Pathfinding/Path.hpp"

namespace swift
{
	const float MAX_ZOOM = 2.f;
	const float MIN_ZOOM = 0.5f;

	Play::Play(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic)
	:	State(win, am, sp, mp, set, dic),
	    activeState(nullptr),
		playView({0, 0, static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y)}),
		currentZoom(1.f),
		activeWorld(nullptr),
		player(nullptr)
	{
		returnType = State::Type::Play;

		// setup SubStates
		play.setEventFunc([&](sf::Event& e)
		{
			hud.update(e);

			switch(e.type)
			{
				case sf::Event::LostFocus:
					if(player)
						if(player->has<Movable>())
							player->get<Movable>()->velocity = {0, 0};
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
				playView.setCenter(std::floor(player->get<Physical>()->position.x), std::floor(player->get<Physical>()->position.y));
				soundPlayer.setListenerPosition({player->get<Physical>()->position.x, player->get<Physical>()->position.y, 0});
			}
			else
			{
				playView.setCenter(0, 0);
				soundPlayer.setListenerPosition({0, 0, 0});
			}
		});

		play.setDrawFunc([&](float)
		{
			window.setView(playView);
			activeWorld->drawWorld(window);
			activeWorld->drawEntities(window);

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

	Play::~Play()
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

	void Play::setup()
	{
		window.setKeyRepeatEnabled(false);
		
		std::ifstream fin;
		
		std::string worldName;
		std::string tilemapFile;
		
		fin.open("./data/saves/currentWorld");
		std::getline(fin, worldName);
		std::getline(fin, tilemapFile);
		fin.close();

		// create worlds
		changeWorld(worldName, tilemapFile);

		Script::setPlayState(*this);
		Script::setWorld(*activeWorld);

		addScript("./data/scripts/worlds.lua");

		setupKeyBindings();
		setupGUI();

		// set the active state
		activeState = &play;
	}

	void Play::handleEvent(sf::Event& event)
	{
		if(event.type == sf::Event::MouseWheelMoved)
		{
			// a positive event.mouseWheel.delta is into the screen
			// negative is out
			float previousZoom = currentZoom;
			if(event.mouseWheel.delta != 1.f)
				currentZoom *= 2.f;
			else
				currentZoom *= 0.5f;

			if(currentZoom >= MAX_ZOOM)
				currentZoom = MAX_ZOOM;
			else if(currentZoom <= MIN_ZOOM)
				currentZoom = MIN_ZOOM;

			playView.zoom(currentZoom / previousZoom);
		}

		activeState->handleEvents(event);

		keyboard(event);
		mouse(event);
	}

	void Play::update(sf::Time dt)
	{
		activeState->update(dt);

		soundPlayer.update();
		musicPlayer.update();

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

	void Play::draw(float e)
	{
		activeState->draw(e);
	}

	bool Play::switchFrom()
	{
		return returnType != State::Type::Play;
	}

	State::Type Play::finish()
	{
		return returnType;
	}

	Entity* Play::getPlayer() const
	{
		return player;
	}

	bool Play::addScript(const std::string& scriptFile)
	{
		if(scripts.find(scriptFile) == scripts.end())
		{
			scripts.emplace(scriptFile, &assets.getScript(scriptFile));
			scripts[scriptFile]->start();
			return true;
		}
		else
			return false;
	}

	bool Play::removeScript(const std::string& scriptFile)
	{
		if(scripts.find(scriptFile) != scripts.end())
		{
			if(!scripts[scriptFile]->save("./data/saves/" + scriptFile.substr(scriptFile.find_last_of('/') + 1) + ".script"))
				log << "[ERROR]: Could not save script: " << scriptFile << "!\n";
			scripts[scriptFile]->reset();
			scripts.erase(scriptFile);
			return true;
		}
		else
			return false;
	}

	void Play::changeWorld(const std::string& name, const std::string& mapFile)
	{
		worlds.emplace(name, new World(name, assets, soundPlayer, musicPlayer, {}));
		World* newWorld = worlds[name];

		// setup world
		bool mapResult = newWorld->tilemap.loadFile(mapFile);
		bool textureResult = newWorld->tilemap.loadTexture(assets.getTexture(newWorld->tilemap.getTextureFile()));

		if(!mapResult)
			log << "[ERROR]: Loading tilemap \"" << mapFile << "\" failed.\n";

		if(!textureResult)
			log << "[ERROR]: Setting texture for \"" << mapFile << "\" failed.\n";

		if(!mapResult || !textureResult)
		{
			worlds.erase(name);	// undo what we did and exit since loading the world failed
			return;
		}

		// get the player
		if(activeWorld)
		{
			// copy over play from current world to new world
			Entity* newPlayer = newWorld->addEntity();
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
				log << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
		}
		else
		{
			// load the world's save file
			bool loadResult = newWorld->load();
			
			if(!loadResult)
				log << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
			
			for(auto& e : newWorld->getEntities())
			{
				if(e->has<Controllable>())
				{
					player = e;
					break;
				}
			}
		}

		activeWorld = newWorld;
		Script::setWorld(*activeWorld);
	}

	void Play::setupGUI()
	{
		// setup pause menu GUI
		std::string resume = "Resume";
		dictionary.get("resumeButton", resume);
		cstr::Column& pauseColumn = pauseMenu.addContainer(new cstr::Column( {static_cast<int>(window.getSize().x) / 2 - 50, static_cast<int>(window.getSize().y / 2) - 50, 100, 125}, false));
		pauseColumn.addWidget(new cstr::Button( {100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			activeState = &play;
		})).setString(resume, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);

		pauseColumn.addWidget(new cstr::Spacer( {100, 25}));

		std::string mainMenu = "Main Menu";
		dictionary.get("mainMenuButton", mainMenu);
		pauseColumn.addWidget(new cstr::Button( {100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::MainMenu;
		})).setString(mainMenu, assets.getFont("./data/fonts/segoeuisl.ttf"), 20);
	}

	void Play::setupKeyBindings()
	{
		keyboard.newBinding("PauseMenu", sf::Keyboard::Escape, [&]()
		{
			activeState = (activeState == &pause) ? &play : &pause;
		}, false);

		// move up press and release
		keyboard.newBinding("moveUpStart", sf::Keyboard::Up, [&]()
		{
			if(player)
				if(player->has<Controllable>())
					player->get<Controllable>()->moveUp = true;
		}, true);

		keyboard.newBinding("moveUpStop", sf::Keyboard::Up, [&]()
		{
			if(player)
				if(player->has<Controllable>())
					player->get<Controllable>()->moveUp = false;
		}, false);

		// move down press and release
		keyboard.newBinding("moveDownStart", sf::Keyboard::Down, [&]()
		{
			if(player)
				if(player->has<Controllable>())
					player->get<Controllable>()->moveDown = true;
		}, true);

		keyboard.newBinding("moveDownStop", sf::Keyboard::Down, [&]()
		{
			if(player)
				if(player->has<Controllable>())
					player->get<Controllable>()->moveDown = false;
		}, false);

		// move left press and release
		keyboard.newBinding("moveLeftStart", sf::Keyboard::Left, [&]()
		{
			if(player)
				if(player->has<Controllable>())
					player->get<Controllable>()->moveLeft = true;
		}, true);

		keyboard.newBinding("moveLeftStop", sf::Keyboard::Left, [&]()
		{
			if(player)
				if(player->has<Controllable>())
					player->get<Controllable>()->moveLeft = false;
		}, false);

		// move right press and release
		keyboard.newBinding("moveRightStart", sf::Keyboard::Right, [&]()
		{
			if(player)
				if(player->has<Controllable>())
					player->get<Controllable>()->moveRight = true;
		}, true);

		keyboard.newBinding("moveRightStop", sf::Keyboard::Right, [&]()
		{
			if(player)
				if(player->has<Controllable>())
					player->get<Controllable>()->moveRight = false;
		}, false);
	}
}
