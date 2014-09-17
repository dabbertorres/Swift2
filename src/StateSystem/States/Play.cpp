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
	Play::Play(sf::RenderWindow& win, AssetManager& am)
		:	State(win, am),
		    state(SubState::Play),
			world({static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y)}, assets)
	{
		returnType = State::Type::Play;
	}

	Play::~Play()
	{
		player = nullptr;
	}

	void Play::setup()
	{
		window.setKeyRepeatEnabled(false);
		Script* playSetup = &assets.getScript("./data/scripts/play.lua");
		Script* pauseSetup = &assets.getScript("./data/scripts/pause.lua");

		if(playSetup == nullptr)
			std::cerr << "Play script isn't being loaded\n";
		if(pauseSetup == nullptr)
			std::cerr << "Pause script isn't being loaded\n";

		playSetup->setGUI(hud);
		playSetup->setStateReturn(returnType);
		playSetup->setKeyboard(keyboard);
		playSetup->start();

		pauseSetup->setGUI(pauseMenu);
		pauseSetup->setStateReturn(returnType);
		pauseSetup->setKeyboard(keyboard);
		pauseSetup->start();

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
			std::cout << "Setting up vertices for \'./data/maps/maze.map\' failed\n";
		
		player = &world.getEntities()[0];
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
				world.draw(window);
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
			player->get<Movable>()->velocity += {0, -player->get<Movable>()->moveVelocity};
		}, true);
		
		keyboard.newBinding("moveUpStop", sf::Keyboard::Up, [&]()
		{
			player->get<Movable>()->velocity += {0, player->get<Movable>()->moveVelocity};
		}, false);
		
		// move down press and release
		keyboard.newBinding("moveDownStart", sf::Keyboard::Down, [&]()
		{
			player->get<Movable>()->velocity += {0, player->get<Movable>()->moveVelocity};
		}, true);
		
		keyboard.newBinding("moveDownStop", sf::Keyboard::Down, [&]()
		{
			player->get<Movable>()->velocity += {0, -player->get<Movable>()->moveVelocity};
		}, false);
		
		// move left press and release
		keyboard.newBinding("moveLeftStart", sf::Keyboard::Left, [&]()
		{
			player->get<Movable>()->velocity += {-player->get<Movable>()->moveVelocity, 0};
		}, true);
		
		keyboard.newBinding("moveLeftStop", sf::Keyboard::Left, [&]()
		{
			player->get<Movable>()->velocity += {player->get<Movable>()->moveVelocity, 0};
		}, false);
		
		// move right press and release
		keyboard.newBinding("moveRightStart", sf::Keyboard::Right, [&]()
		{
			player->get<Movable>()->velocity += {player->get<Movable>()->moveVelocity, 0};
		}, true);
		
		keyboard.newBinding("moveRightStop", sf::Keyboard::Right, [&]()
		{
			player->get<Movable>()->velocity += {-player->get<Movable>()->moveVelocity, 0};
		}, false);
	}
}
