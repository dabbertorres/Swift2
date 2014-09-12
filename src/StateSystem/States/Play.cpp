#include "Play.hpp"

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
		    state(SubState::Play)
	{
		returnType = State::Type::Play;
	}

	Play::~Play()
	{
	}

	void Play::setup()
	{
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

	void Play::update(sf::Time /*dt*/)
	{
		Script* playLogic = &assets.getScript("./data/scripts/play.lua");
		Script* pauseLogic = &assets.getScript("./data/scripts/pause.lua");

		switch(state)
		{
			case SubState::Play:
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
		return returnType;
	}

	void Play::setupKeyBindings()
	{
		keyboard.newBinding("PauseMenu", sf::Keyboard::Escape, [&]()
		{
			state = (state == SubState::Pause) ? SubState::Play : SubState::Pause;
		}, false);
	}
}
