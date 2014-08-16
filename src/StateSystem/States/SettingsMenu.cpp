#include "SettingsMenu.hpp"

#include "../../ResourceManager/AssetManager.hpp"

namespace swift
{
	SettingsMenu::SettingsMenu(sf::RenderWindow& win, AssetManager& am, Settings& s)
		:	State(win, am),
			settings(s)
	{
		returnType = State::Type::SettingsMenu;
	}

	SettingsMenu::~SettingsMenu()
	{
	}

	void SettingsMenu::setup()
	{
		Script* setup = &assets.getScript("./data/scripts/settingsMenu.lua");
		
		setup->setGUI(gui);
		setup->setStateReturn(returnType);
		setup->start();
	}
	
	void SettingsMenu::handleEvent(sf::Event &event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void SettingsMenu::update(sf::Time /*dt*/)
	{
		Script* setup = &assets.getScript("./data/scripts/settingsMenu.lua");
		
		setup->run();
	}
	
	void SettingsMenu::draw(float /*e*/)
	{
		window.draw(gui);
	}
	
	bool SettingsMenu::switchFrom()
	{
		return returnType != State::Type::SettingsMenu;
	}
	
	State::Type SettingsMenu::finish()
	{
		return returnType;
	}
}
