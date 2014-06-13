#include "SettingsMenu.hpp"

namespace swift
{
	SettingsMenu::SettingsMenu(sf::RenderWindow& win, AssetManager& am)
		:	State(win, am)
	{
		returnType = State::Type::SettingsMenu;
	}

	SettingsMenu::~SettingsMenu()
	{
	}

	void SettingsMenu::setup()
	{
		activeScripts.push_back(&assets.getScript("./data/scripts/settingsMenu.lua"));
		
		for(auto &s : activeScripts)
		{
			s->start();
		}
		
		setupButtons();
	}
	
	void SettingsMenu::handleEvent(sf::Event &event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void SettingsMenu::update(sf::Time /*dt*/)
	{
		updateScripts();
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
	
	void SettingsMenu::setupButtons()
	{
		struct
		{
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
			std::string str = "";
		} mainMenuReturnData;
		
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("mainMenuReturnW", mainMenuReturnData.w);
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("mainMenuReturnH", mainMenuReturnData.h);
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("mainMenuReturnX", mainMenuReturnData.x);
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("mainMenuReturnY", mainMenuReturnData.y);
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("mainMenuReturnStr", mainMenuReturnData.str);
		
		cstr::Button& mainMenuButton = gui.addButton({mainMenuReturnData.x, mainMenuReturnData.y, mainMenuReturnData.w, mainMenuReturnData.h}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::MainMenu;
		});
		
		mainMenuButton.setText(mainMenuReturnData.str);
		mainMenuButton.setFont(assets.getFont("./data/fonts/DroidSansMono.ttf"));
	}
}
