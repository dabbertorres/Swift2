#include "MainMenu.hpp"

#include "../../ResourceManager/AssetManager.hpp"

/* GUI headers */
#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Spacer.hpp"

/* SoundSystem headers */
#include "../../SoundSystem/SoundPlayer.hpp"
#include "../../SoundSystem/MusicPlayer.hpp"

namespace swift
{
	MainMenu::MainMenu(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic)
		:	State(win, am, sp, mp, set, dic)
	{		
		returnType = State::Type::MainMenu;
	}

	MainMenu::~MainMenu()
	{
	}
	
	void MainMenu::setup()
	{
		window.setKeyRepeatEnabled(true);
		
		cstr::Column& titleColumn = gui.addContainer(new cstr::Column({300, 0, 200, 600}, false));
		
		titleColumn.addWidget(new cstr::Spacer({200, 100}));
		
		std::string title = "Swift2";
		dictionary.get("titleLabel", title);
		titleColumn.addWidget(new cstr::Label("Swift2", assets.getFont("./data/fonts/segoeuisl.ttf"), 60));
		
		titleColumn.addWidget(new cstr::Spacer({200, 100}));
		
		cstr::Column& buttonColumn = titleColumn.addWidget(new cstr::Column({100, 200}, false));
		
		std::string start = "Start";
		dictionary.get("startButton", start);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::Play;
		})).setString(start, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string settings = "Settings";
		dictionary.get("settingButton", settings);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::SettingsMenu;
		})).setString(settings, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string exit = "Start";
		dictionary.get("exitButton", exit);
		buttonColumn.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::Exit;
		})).setString(exit, assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
	}
	
	void MainMenu::handleEvent(sf::Event &event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void MainMenu::update(sf::Time /*dt*/)
	{
		soundPlayer.update();
		musicPlayer.update();
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
