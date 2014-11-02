#include "Play.hpp"

#include "../../ResourceManager/AssetManager.hpp"

/* GUI headers */
#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Spacer.hpp"

/* Worlds */
#include "../../World/Worlds/TestWorld.hpp"

namespace swift
{
	Play::Play(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic)
		:	State(win, am, sp, mp, set, dic),
		    activeState(nullptr),
			playView({0, 0, static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y)}),
			activeWorld(nullptr),
			player(nullptr)
	{
		returnType = State::Type::Play;
	}

	Play::~Play()
	{
		for(auto& w : worlds)
			delete w;
	}

	void Play::setup()
	{
		window.setKeyRepeatEnabled(false);
		
		worlds.emplace_back(new TestWorld("testWorld", {800, 600}, assets));
		activeWorld = worlds[0];
		
		setupKeyBindings();
		setupGUI();
		
		// setup SubStates
		play.setEventFunc([&](sf::Event& e)
		{
			hud.update(e);
		});
		
		play.setUpdateFunc([&](sf::Time dt)
		{
			activeWorld->update(dt.asSeconds());
			playView.setCenter({std::floor(player->get<Physical>()->position.x), std::floor(player->get<Physical>()->position.y)});
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
		
		// set the active state
		activeState = &play;
		
		// setup world
		bool loadResult = activeWorld->tilemap.loadFile("./data/maps/maze.map");
		bool textureResult = activeWorld->tilemap.loadTexture(assets.getTexture(activeWorld->tilemap.getTextureFile()));
		
		if(!loadResult)
			std::cerr << "load failed\n";
		
		if(!textureResult)
			std::cerr << "texture failed\n";
		
		// loading fails, so create a player
		if(!activeWorld->load())
		{
			player = activeWorld->addEntity();
			player->add<Drawable>();
			Drawable* drawable = player->get<Drawable>();
			sf::Texture& texture = assets.getTexture("./data/textures/guy.png");
			drawable->texture = "./data/textures/guy.png";
			drawable->sprite.setTexture(texture);
			drawable->sprite.setScale({16.f / texture.getSize().x, 48.f / texture.getSize().y});
			
			player->add<Name>();
			Name* name = player->get<Name>();
			name->name = "player";
			
			player->add<Physical>();
			Physical* physical = player->get<Physical>();
			physical->size = {16, 48};
			physical->position = {window.getSize().x / 2.f, 500};
			
			player->add<Movable>();
			Movable* movable = player->get<Movable>();
			movable->moveVelocity = 100;
			movable->velocity = {0, 0};
		}
		// loading suceeds, so get the player
		else
			player = activeWorld->getEntities()[0];
		
		activeWorld->addScript("./data/scripts/quest.lua");
		assets.getScript("./data/scripts/quest.lua").start();
	}

	void Play::handleEvent(sf::Event& event)
	{
		activeState->handleEvents(event);

		keyboard(event);
		mouse(event);
	}

	void Play::update(sf::Time dt)
	{
		activeState->update(dt);
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
	
	void Play::setupGUI()
	{
		// setup pause menu GUI
		std::string resume = "Resume";
		dictionary.get("resumeButton", resume);
		cstr::Column& pauseColumn = pauseMenu.addContainer(new cstr::Column({static_cast<int>(window.getSize().x) / 2 - 50, static_cast<int>(window.getSize().y / 2) - 50, 100, 125}, false));
		pauseColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			activeState = &play;
		})).setString(resume, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		pauseColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string mainMenu = "Main Menu";
		dictionary.get("mainMenuButton", mainMenu);
		pauseColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
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
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {0, -player->get<Movable>()->moveVelocity};
		}, true);
		
		keyboard.newBinding("moveUpStop", sf::Keyboard::Up, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {0, player->get<Movable>()->moveVelocity};
		}, false);
		
		// move down press and release
		keyboard.newBinding("moveDownStart", sf::Keyboard::Down, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {0, player->get<Movable>()->moveVelocity};
		}, true);
		
		keyboard.newBinding("moveDownStop", sf::Keyboard::Down, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {0, -player->get<Movable>()->moveVelocity};
		}, false);
		
		// move left press and release
		keyboard.newBinding("moveLeftStart", sf::Keyboard::Left, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {-player->get<Movable>()->moveVelocity, 0};
		}, true);
		
		keyboard.newBinding("moveLeftStop", sf::Keyboard::Left, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {player->get<Movable>()->moveVelocity, 0};
		}, false);
		
		// move right press and release
		keyboard.newBinding("moveRightStart", sf::Keyboard::Right, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {player->get<Movable>()->moveVelocity, 0};
		}, true);
		
		keyboard.newBinding("moveRightStop", sf::Keyboard::Right, [&]()
		{
			if(player)
				if(player->has<Movable>())
					player->get<Movable>()->velocity += {-player->get<Movable>()->moveVelocity, 0};
		}, false);
	}
}
