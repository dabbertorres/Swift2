#include "MainMenu.hpp"

namespace swift
{
	MainMenu::MainMenu(sf::RenderWindow& win, AssetManager& am)
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
		
		returnType = State::Type::MainMenu;
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
		
		struct
		{
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
			std::string str = "";
		} startButtonData;
		
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonX", startButtonData.x);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonY", startButtonData.y);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonW", startButtonData.w);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonH", startButtonData.h);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("startButtonStr", startButtonData.str);
		
		cstr::Button& startButton = gui.addButton({startButtonData.x, startButtonData.y, startButtonData.w, startButtonData.h}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::Play;
		});
		
		startButton.setText(startButtonData.str);
		startButton.setFont(assets.getFont("./data/fonts/DroidSansMono.ttf"));
		
		struct
		{
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
			std::string str = "";
		} exitButtonData;
		
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("exitButtonX", exitButtonData.x);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("exitButtonY", exitButtonData.y);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("exitButtonW", exitButtonData.w);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("exitButtonH", exitButtonData.h);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("exitButtonStr", exitButtonData.str);
		
		cstr::Button& exitButton = gui.addButton({exitButtonData.x, exitButtonData.y, exitButtonData.w, exitButtonData.h}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::Exit;
		});
		
		exitButton.setText(exitButtonData.str);
		exitButton.setFont(assets.getFont("./data/fonts/DroidSansMono.ttf"));
	}
	
	void MainMenu::handleEvent(sf::Event &event)
	{
		gui.update(event);
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
	
	bool MainMenu::switchFrom()
	{
		return returnType != State::Type::MainMenu;
	}
	
	State::Type MainMenu::finish()
	{
		return returnType;
	}
}
