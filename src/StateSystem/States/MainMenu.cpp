#include "MainMenu.hpp"

namespace swift
{
	MainMenu::MainMenu(sf::RenderWindow& win, AssetManager& am, sf::Font& font)
		:	State(win, am)
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
		activeScripts.push_back(&assets.getScript("./data/scripts/mainMenu.lua"));
		
		for(auto &s : activeScripts)
		{
			s->start();
		}
		
		int startButtonX = 0;
		int startButtonY = 0;
		int startButtonW = 0;
		int startButtonH = 0;
		std::string startButtonStr = "";
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonX", startButtonX);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonY", startButtonY);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonW", startButtonW);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonH", startButtonH);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonStr", startButtonStr);
		
		cstr::Button& startButton = gui.addButton({startButtonX, startButtonY, startButtonW, startButtonH}, assets.getTexture("./data/textures/button.png"), [](){});
		startButton.setText(startButtonStr);
		startButton.setFont(assets.getFont("./data/fonts/DroidSansMono.ttf"));
	}
	
	void MainMenu::switchTo()
	{
		
	}
	
	void MainMenu::handleEvent(sf::Event &event)
	{
		keyboard(event);
		mouse(event);
		gui.update(event);
	}
	
	void MainMenu::update(sf::Time dt)
	{
		updateScripts();
	}
	
	void MainMenu::draw(float e)
	{
		window.draw(gui);
	}
	
	State::Type MainMenu::switchFrom()
	{
		return State::Type::MainMenu;
	}
	
	void MainMenu::finish()
	{
		
	}
}
