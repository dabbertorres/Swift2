#include "SettingsMenu.hpp"

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
		activeScripts.push_back(&assets.getScript("./data/scripts/settingsMenu.lua"));
		
		for(auto& s : activeScripts)
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
		
		bool vsyncState = gui.getWidget(1).getState();
		settings.set("vsync", vsyncState);
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
		// return to mainMenu button
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
		
		// v-sync toggle
		struct
		{
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
			std::string str = "";
		} vsyncToggleData;
		
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("vsyncW", vsyncToggleData.w);
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("vsyncH", vsyncToggleData.h);
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("vsyncX", vsyncToggleData.x);
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("vsyncY", vsyncToggleData.y);
		assets.getScript("./data/scripts/settingsMenu.lua").getVariable("vsyncStr", vsyncToggleData.str);
		
		bool vsyncState;
		settings.get("vsync", vsyncState);
		
		cstr::Toggle& vsyncToggle = gui.addToggle(	{vsyncToggleData.x, vsyncToggleData.y, vsyncToggleData.w, vsyncToggleData.h},
													assets.getTexture("./data/textures/toggleOff.png"),
													assets.getTexture("./data/textures/toggleOn.png"),
													vsyncState);
		
		cstr::Label& vsyncLabel = gui.addLabel({static_cast<float>(vsyncToggleData.x), 
												static_cast<float>(vsyncToggleData.y - 40)},
												vsyncToggleData.str,
												assets.getFont("./data/fonts/DroidSansMono.ttf"));
	}
}
