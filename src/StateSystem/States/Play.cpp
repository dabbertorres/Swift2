#include "Play.hpp"

#include "../../ResourceManager/AssetManager.hpp"

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
		
		playSetup->setGUI(hud);
		playSetup->setStateReturn(returnType);
		playSetup->start();
		
		pauseSetup->setGUI(pauseMenu);
		pauseSetup->setKeyboard(keyboard);
		pauseSetup->setStateReturn(returnType);
		pauseSetup->start();
		
		setupKeyBindings();
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
