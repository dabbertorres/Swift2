#include "MainMenu.hpp"

#include "../../ResourceManager/AssetManager.hpp"

namespace swift
{
	MainMenu::MainMenu(sf::RenderWindow& win, AssetManager& am)
		:	State(win, am)
	{		
		returnType = State::Type::MainMenu;
	}

	MainMenu::~MainMenu()
	{
	}
	
	void MainMenu::setup()
	{
		Script* setup = &assets.getScript("./data/scripts/mainMenu.lua");
		
		setup->setGUI(gui);
		setup->setStateReturn(returnType);
		setup->start();
	}
	
	void MainMenu::handleEvent(sf::Event &event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void MainMenu::update(sf::Time /*dt*/)
	{
		
	}
	
	void MainMenu::draw(float /*e*/)
	{
		window.draw(gui);
	}
	
	bool MainMenu::switchFrom()
	{
		return returnType != State::Type::MainMenu;
	}
	
	State::Type MainMenu::finish()
	{
		return returnType;
	}
}
