#include "MainMenu.hpp"

#include "../../ResourceManager/AssetManager.hpp"

/* GUI headers */
#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Spacer.hpp"

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
		window.setKeyRepeatEnabled(true);
		Script* setup = &assets.getScript("./data/scripts/mainMenu.lua");
		
		setup->setGUI(gui);
		setup->setStateReturn(returnType);
		setup->start();
		
		cstr::Column& titleColumn = gui.addContainer(new cstr::Column({300, 0, 200, 600}, false));
		
		titleColumn.addWidget(new cstr::Spacer({200, 100}));
		
		titleColumn.addWidget(new cstr::Label("Swift2", assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		titleColumn.addWidget(new cstr::Spacer({200, 100}));
		
		cstr::Column& buttonColumn = titleColumn.addWidget(new cstr::Column({100, 200}, false));
		
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::Play;
		})).setString("Start", assets.getFont("./data/fonts/segoeuisl.ttf"));
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::SettingsMenu;
		})).setString("Settings", assets.getFont("./data/fonts/segoeuisl.ttf"));
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::Exit;
		})).setString("Exit", assets.getFont("./data/fonts/segoeuisl.ttf"));
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
