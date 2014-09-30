#include "Play.hpp"

#include <functional>

#include "../../ResourceManager/AssetManager.hpp"

/* GUI headers */
#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Spacer.hpp"

namespace swift
{
	Play::Play(sf::RenderWindow& win, AssetManager& am, Settings& set, Settings& dic)
		:	State(win, am, set, dic),
		    state(SubState::Play),
			world({static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y)}, assets),
			player(nullptr)
	{
		returnType = State::Type::Play;
	}

	Play::~Play()
	{
		//player = nullptr;
	}

	void Play::setup()
	{
		window.setKeyRepeatEnabled(false);
		Script* playSetup = &assets.getScript("./data/scripts/play.lua");
		Script* pauseSetup = &assets.getScript("./data/scripts/pause.lua");
		
		if(playSetup == nullptr)
			log << "Play script wasn't loaded\n";
		else
		{
			playSetup->setGUI(hud);
			playSetup->setStateReturn(returnType);
			playSetup->setKeyboard(keyboard);
			playSetup->setWorld(world);
			playSetup->start();
		}
		if(pauseSetup == nullptr)
			log << "Pause script wasn't loaded\n";
		else
		{
			pauseSetup->setGUI(pauseMenu);
			pauseSetup->setStateReturn(returnType);
			pauseSetup->setKeyboard(keyboard);
			pauseSetup->start();
		}
		
		setupKeyBindings();
		
		// setup pause menu GUI
		cstr::Column& pauseColumn = pauseMenu.addContainer(new cstr::Column({static_cast<int>(window.getSize().x) / 2 - 50, static_cast<int>(window.getSize().y / 2) - 50, 100, 125}, false));
		pauseColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			state = SubState::Play;
		})).setString("Resume", assets.getFont("./data/fonts/segoeuisl.ttf"));
		
		pauseColumn.addWidget(new cstr::Spacer({100, 25}));
		
		pauseColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::MainMenu;
		})).setString("Main Menu", assets.getFont("./data/fonts/segoeuisl.ttf"));
		
		// World test code
		world.load("");
		bool result = world.tilemap.loadFile("./data/maps/maze.map");
		
		if(!result)
			log << "Loading \'./data/maps/maze.map\' failed\n";
		
		result = world.tilemap.load(assets.getTexture(world.tilemap.getTextureFile()));
		
		if(!result)
			log << "Setting up vertices for \'./data/maps/maze.map\' failed\n";
		
		// setup player
		player = world.addEntity();
		player->add<Drawable>();
		player->add<Physical>();
		player->add<Name>();
		player->get<Name>()->name = "player";
		player->add<Movable>();
		
		player->get<Drawable>()->sprite.setTexture(assets.getTexture("./data/textures/guy.png"));
		player->get<Drawable>()->sprite.setScale({0.5f, (player->get<Drawable>()->sprite.getGlobalBounds().height - 16) / player->get<Drawable>()->sprite.getGlobalBounds().height});
		
		player->get<Physical>()->position = {400, 300};
		player->get<Physical>()->size = {static_cast<unsigned>(player->get<Drawable>()->sprite.getGlobalBounds().width),
										static_cast<unsigned>(player->get<Drawable>()->sprite.getGlobalBounds().height)};
		
		player->get<Movable>()->moveVelocity = 100;
	}

	void Play::handleEvent(sf::Event& event)
	{
		switch(state)
		{
			case SubState::Play:
				hud.update(event);
				break;
			case SubState::Pause:
				pauseMenu.update(event);
				break;
			default:
				break;
		}

		keyboard(event);
		mouse(event);
	}

	void Play::update(sf::Time dt)
	{
		Script* playLogic = &assets.getScript("./data/scripts/play.lua");
		Script* pauseLogic = &assets.getScript("./data/scripts/pause.lua");
		
		switch(state)
		{
			case SubState::Play:
				world.update(dt.asSeconds());
				playLogic->run();
				break;
			case SubState::Pause:
				pauseLogic->run();
				break;
		}
	}

	void Play::draw(float /*e*/)
	{
		switch(state)
		{
			case SubState::Play:
				window.draw(world);
				
				window.draw(hud);
				break;
			case SubState::Pause:
				window.draw(pauseMenu);
				break;
			default:
				break;
		}
	}

	bool Play::switchFrom()
	{
		return returnType != State::Type::Play;
	}

	State::Type Play::finish()
	{
		world.save("");
		return returnType;
	}

	void Play::setupKeyBindings()
	{
		keyboard.newBinding("PauseMenu", sf::Keyboard::Escape, [&]()
		{
			state = (state == SubState::Pause) ? SubState::Play : SubState::Pause;
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
