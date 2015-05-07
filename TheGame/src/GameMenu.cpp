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
	GameMenu::GameMenu(sf::RenderWindow& win, swift::AssetManager& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set,
	                   swift::Settings& dic, swift::StateMachine& sm, const std::string& rp)
		:	State(win, am, sp, mp, set, dic, sm, rp)
	{
		window.setKeyRepeatEnabled(true);

		setupGUI();
	}

	GameMenu::~GameMenu()
	{
	}

	void GameMenu::handleEvent(sf::Event& event)
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
		auto* font = assets.getFont("segoeuisl.ttf");
		auto* buttonTexture = assets.getTexture("button.png");

		if(!font)
		{
			swift::log << "[ERROR]: Could not find segoeuisl.ttf!\n";
			return;
		}

		if(!buttonTexture)
		{
			swift::log << "[ERROR]: Could not find button.png!\n";
			return;
		}

		cstr::Column& titleColumn = gui.addContainer(new cstr::Column( {300, 0, 200, 600}, false));

		titleColumn.addWidget(new cstr::Spacer( {200, 100}));

		std::string title = "Swift2";
		dictionary.get("titleLabel", title);
		titleColumn.addWidget(new cstr::Label("Swift2", *font, 60));

		titleColumn.addWidget(new cstr::Spacer( {200, 100}));

		cstr::Column& buttonColumn = titleColumn.addWidget(new cstr::Column( {100, 200}, false));

		std::string start = "Start";
		dictionary.get("startButton", start);
		buttonColumn.addWidget(new cstr::Button( {100, 50}, *buttonTexture, [&]()
		{
			shouldReturn = true;
			states.push(new GamePlay(window, assets, soundPlayer, musicPlayer, settings, dictionary, states, resPath));
		})).setString(start, *font, 25);

		buttonColumn.addWidget(new cstr::Spacer( {100, 25}));

		std::string settingsStr = "Settings";
		dictionary.get("settingButton", settingsStr);
		buttonColumn.addWidget(new cstr::Button( {100, 50}, *buttonTexture, [&]()
		{
			shouldReturn = true;
			states.push(new GameSettings(window, assets, soundPlayer, musicPlayer, settings, dictionary, states, resPath));
		})).setString(settingsStr, *font, 25);

		buttonColumn.addWidget(new cstr::Spacer( {100, 25}));

		std::string exit = "Exit";
		dictionary.get("exitButton", exit);
		buttonColumn.addWidget(new cstr::Button( {100, 50}, *buttonTexture, [&]()
		{
			shouldReturn = true;
		})).setString(exit, *font, 25);
	}
}
