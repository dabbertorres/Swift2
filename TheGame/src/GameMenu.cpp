#include "GameMenu.hpp"

#include "../src/ResourceManager/AssetManager.hpp"

/* SoundSystem headers */
#include "../src/SoundSystem/SoundPlayer.hpp"
#include "../src/SoundSystem/MusicPlayer.hpp"

/* GUI headers */
#include "../src/GUI/Containers/Column.hpp"
#include "../src/GUI/Containers/Row.hpp"
#include "../src/GUI/Widgets/Label.hpp"
#include "../src/GUI/Widgets/Button.hpp"
#include "../src/GUI/Widgets/Spacer.hpp"

#include "../src/Settings/Settings.hpp"

#include "GamePlay.hpp"
#include "GameSettings.hpp"

namespace tg
{
	GameMenu::GameMenu(sf::RenderWindow& win, swift::AssetManager& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic, swift::StateMachine& sm)
	:	State(win, am, sp, mp, set, dic, sm)
	{
		window.setKeyRepeatEnabled(true);
		
		setupGUI();
	}

	GameMenu::~GameMenu()
	{
	}
	
	void GameMenu::handleEvent(sf::Event &event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void GameMenu::update(sf::Time /*dt*/)
	{
		soundPlayer.update();
		musicPlayer.update();
	}
	
	void GameMenu::draw(float /*e*/)
	{
		window.draw(gui);
	}
	
	void GameMenu::setupGUI()
	{
		cstr::Column& titleColumn = gui.addContainer(new cstr::Column({300, 0, 200, 600}, false));
		
		titleColumn.addWidget(new cstr::Spacer({200, 100}));
		
		std::string title = "Swift2";
		dictionary.get("titleLabel", title);
		titleColumn.addWidget(new cstr::Label("Swift2", *assets.getFont("./data/fonts/segoeuisl.ttf"), 60));
		
		titleColumn.addWidget(new cstr::Spacer({200, 100}));
		
		cstr::Column& buttonColumn = titleColumn.addWidget(new cstr::Column({100, 200}, false));
		
		std::string start = "Start";
		dictionary.get("startButton", start);
		buttonColumn.addWidget(new cstr::Button({100, 50}, *assets.getTexture("./data/textures/button.png"), [&]()
		{
			shouldReturn = true;
			states.push(new GamePlay(window, assets, soundPlayer, musicPlayer, settings, dictionary, states));
		})).setString(start, *assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string settingsStr = "Settings";
		dictionary.get("settingButton", settingsStr);
		buttonColumn.addWidget(new cstr::Button({100, 50}, *assets.getTexture("./data/textures/button.png"), [&]()
		{
			shouldReturn = true;
			states.push(new GameSettings(window, assets, soundPlayer, musicPlayer, settings, dictionary, states));
		})).setString(settingsStr, *assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
		
		buttonColumn.addWidget(new cstr::Spacer({100, 25}));
		
		std::string exit = "Start";
		dictionary.get("exitButton", exit);
		buttonColumn.addWidget(new cstr::Button({100, 50}, *assets.getTexture("./data/textures/button.png"), [&]()
		{
			shouldReturn = true;
		})).setString(exit, *assets.getFont("./data/fonts/segoeuisl.ttf"), 25);
	}
}
