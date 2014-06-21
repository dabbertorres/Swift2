#include "MainMenu.hpp"

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
		activeScripts.push_back(&assets.getScript("./data/scripts/mainMenu.lua"));
		
		for(auto &s : activeScripts)
		{
			s->start();
		}
		
		setupButtons();
	}
	
	void MainMenu::handleEvent(sf::Event &event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void MainMenu::update(sf::Time /*dt*/)
	{
		updateScripts();
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
	
	void MainMenu::setupButtons()
	{
		// title
		struct
		{
			int x = 0;
			int y = 0;
			unsigned size = 0;
			std::string str = "";
		} titleLabelData;
		
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("titleLabelX", titleLabelData.x);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("titleLabelY", titleLabelData.y);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("titleLabelSize", titleLabelData.size);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("titleLabelStr", titleLabelData.str);
		
		cstr::Label& titleLabel = gui.addLabel({static_cast<float>(titleLabelData.x), static_cast<float>(titleLabelData.y)}, 
												titleLabelData.str, assets.getFont("./data/fonts/DroidSansMono.ttf"));
		titleLabel.setCharacterSize(titleLabelData.size);
		
		// start/play button
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
		
		// settings button
		struct
		{
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
			std::string str = "";
		} settingsButtonData;
		
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("settingsButtonX", settingsButtonData.x);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("settingsButtonY", settingsButtonData.y);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("settingsButtonW", settingsButtonData.w);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("settingsButtonH", settingsButtonData.h);
		assets.getScript("./data/scripts/mainMenu.lua").getVariable("settingsButtonStr", settingsButtonData.str);
		
		cstr::Button& settingsButton = gui.addButton({settingsButtonData.x, settingsButtonData.y, settingsButtonData.w, settingsButtonData.h}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::SettingsMenu;
		});
		
		settingsButton.setText(settingsButtonData.str);
		settingsButton.setFont(assets.getFont("./data/fonts/DroidSansMono.ttf"));
		
		// exit button
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
}
