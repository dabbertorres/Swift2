#include "MainMenu.hpp"

namespace swift
{
	MainMenu::MainMenu(sf::RenderWindow& win, AssetManager& am, sf::Font& font)
		:	State(win, am),
			gui(win, font, 14, false)
	{
		keyboard.newBinding("up", sf::Keyboard::W, []()
		{
			std::clog << "\'Up\' was pressed!\n";
		});
		
		keyboard.newBinding("left", sf::Keyboard::A, []()
		{
			std::clog << "\'Left\' was pressed!\n";
		});
		
		keyboard.newBinding("right", sf::Keyboard::D, []()
		{
			std::clog << "\'Right\' was pressed!\n";
		});
		
		keyboard.newBinding("down", sf::Keyboard::S, []()
		{
			std::clog << "\'Down\' was pressed!\n";
		});
	}

	MainMenu::~MainMenu()
	{
	}
	
	void MainMenu::setup()
	{
		activeScripts.push_back(&assets.getScript("./data/scripts/start.lua"));
		
		for(auto &s : activeScripts)
		{
			s->start();
		}
	}
	
	void MainMenu::switchTo()
	{
		
	}
	
	void MainMenu::handleEvent(sf::Event &event)
	{
		keyboard(event);
		mouse(event);
	}
	
	void MainMenu::update(sf::Time dt)
	{
		updateScripts();
	}
	
	void MainMenu::draw(float e)
	{
		window.draw(gui);
	}
	
	void MainMenu::switchFrom()
	{
		
	}
	
	void MainMenu::finish()
	{
		
	}
}
