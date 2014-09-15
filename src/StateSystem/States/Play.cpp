#include "Play.hpp"

#include <functional>

#include "../../ResourceManager/AssetManager.hpp"

/* ECS headers */
#include "../../EntitySystem/Components/Drawable.hpp"
#include "../../EntitySystem/Components/Physical.hpp"
#include "../../EntitySystem/Components/Movable.hpp"

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
		    state(SubState::Play)
	{
		returnType = State::Type::Play;
	}

	Play::~Play()
	{
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
		
		// setup GUI
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
		
		// setup entity
		entities.emplace_back();
		entities[0].add<Drawable>();
		entities[0].add<Physical>();
		entities[0].add<Movable>();
		
		entities[0].get<Drawable>()->sprite.setTexture(assets.getTexture("./data/textures/guy.png"));
		
		entities[0].get<Physical>()->position = {400, 300};
		entities[0].get<Physical>()->size = assets.getTexture("./data/textures/guy.png").getSize();
		entities[0].get<Movable>()->moveVelocity = 100;
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
				playLogic->run();
				for(auto& e : entities)
				{
					moveSystem.update(e, dt.asSeconds());
					physicalSystem.update(e, dt.asSeconds());
					drawSystem.update(e, dt.asSeconds());
				}
				break;
			case SubState::Pause:
				pauseLogic->run();
				break;
		}
	}

	void Play::draw(float /*e*/)
	{
		if(state == SubState::Play)
		{
			for(auto& e : entities)
			{
				drawSystem.draw(e, window);
			}
			window.draw(hud);
		}
		else if(state == SubState::Pause)
		{
			window.draw(pauseMenu);
		}
	}

	bool Play::switchFrom()
	{
		return returnType != State::Type::Play;
	}

	State::Type Play::finish()
	{
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
			entities[0].get<Movable>()->velocity += {0, -entities[0].get<Movable>()->moveVelocity};
		}, true);
		
		keyboard.newBinding("moveUpStop", sf::Keyboard::Up, [&]()
		{
			entities[0].get<Movable>()->velocity += {0, entities[0].get<Movable>()->moveVelocity};
		}, false);
		
		// move down press and release
		keyboard.newBinding("moveDownStart", sf::Keyboard::Down, [&]()
		{
			entities[0].get<Movable>()->velocity += {0, entities[0].get<Movable>()->moveVelocity};
		}, true);
		
		keyboard.newBinding("moveDownStop", sf::Keyboard::Down, [&]()
		{
			entities[0].get<Movable>()->velocity += {0, -entities[0].get<Movable>()->moveVelocity};
		}, false);
		
		// move left press and release
		keyboard.newBinding("moveLeftStart", sf::Keyboard::Left, [&]()
		{
			entities[0].get<Movable>()->velocity += {-entities[0].get<Movable>()->moveVelocity, 0};
		}, true);
		
		keyboard.newBinding("moveLeftStop", sf::Keyboard::Left, [&]()
		{
			entities[0].get<Movable>()->velocity += {entities[0].get<Movable>()->moveVelocity, 0};
		}, false);
		
		// move right press and release
		keyboard.newBinding("moveRightStart", sf::Keyboard::Right, [&]()
		{
			entities[0].get<Movable>()->velocity += {entities[0].get<Movable>()->moveVelocity, 0};
		}, true);
		
		keyboard.newBinding("moveRightStop", sf::Keyboard::Right, [&]()
		{
			entities[0].get<Movable>()->velocity += {-entities[0].get<Movable>()->moveVelocity, 0};
		}, false);
	}
}
