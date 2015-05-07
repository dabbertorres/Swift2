#include "GameSettings.hpp"

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
#include "../src/GUI/Widgets/Slider.hpp"
#include "../src/GUI/Widgets/Toggle.hpp"
#include "../src/GUI/Widgets/TextBox.hpp"

namespace tg
{
	GameSettings::GameSettings(sf::RenderWindow& win, swift::AssetManager& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set,
	                           swift::Settings& dic, swift::StateMachine& sm, const std::string& rs)
		:	State(win, am, sp, mp, set, dic, sm, rs),
		    graphicsButton(nullptr),
		    volumeSlider(nullptr),
		    musicSlider(nullptr)
	{
		window.setKeyRepeatEnabled(true);

		setupGUI();
	}

	void GameSettings::handleEvent(sf::Event& event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}

	void GameSettings::update(sf::Time)
	{
		int sound = volumeSlider->getValue() * 100;
		settings.set("sound", sound);

		int music = musicSlider->getValue() * 100;
		settings.set("music", music);

		soundPlayer.setVolume(sound);
		musicPlayer.setVolume(music);

		soundPlayer.update();
		musicPlayer.update();
	}

	void GameSettings::draw(float)
	{
		window.draw(gui);
	}

	void GameSettings::setupGUI()
	{
		cstr::Column& settingsColumn = gui.addContainer(new cstr::Column( {50, 25, 700, 550}, false));

		std::string settingsStr = "Settings";
		dictionary.get("settingsLabel", settingsStr);
		cstr::Column& titleCol = settingsColumn.addWidget(new cstr::Column( {200, 50}, false));
		titleCol.addWidget(new cstr::Label(settingsStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 60));

		settingsColumn.addWidget(new cstr::Spacer( {700, 25}));

		// row for fullscreen label and toggle
		cstr::Row& fullscreenRow = settingsColumn.addWidget(new cstr::Row( {700, 50}, false));
		cstr::Column& fullscreenLabelCol = fullscreenRow.addWidget(new cstr::Column( {200, 50}, false));
		std::string fullscreen = "Fullscreen";
		dictionary.get("fullscreenLabel", fullscreen);
		fullscreenLabelCol.addWidget(new cstr::Label(fullscreen + ':', *assets.getFont("../data/fonts/segoeuisl.ttf"), 50));

		fullscreenRow.addWidget(new cstr::Spacer( {450, 50}));

		cstr::Column& fullscreenToggleCol = fullscreenRow.addWidget(new cstr::Column( {50, 50}, false));
		bool fullscreenState = false;
		settings.get("fullscreen", fullscreenState);
		fullscreenToggleCol.addWidget(new cstr::Toggle( {50, 50}, *assets.getTexture("../data/textures/toggle.png"), {64, 0, 64, 64}, {0, 0, 64, 64}, fullscreenState,
		                              [&](bool s)
		{
			settings.set("fullscreen", s);

			if(s)
			{
				unsigned resx = 0;
				unsigned resy = 0;
				settings.get("res.x", resx);
				settings.get("res.y", resy);
				window.create( {resx, resy, 32}, "Swift2", sf::Style::Fullscreen);
			}
			else
			{
				unsigned resx = 800;
				unsigned resy = 600;
				settings.get("res.x", resx);
				settings.get("res.y", resy);
				window.create( {resx, resy, 32}, "Swift2", sf::Style::Titlebar | sf::Style::Close);
			}
		}));

		settingsColumn.addWidget(new cstr::Spacer( {700, 25}));

		// row for vsync label and toggle
		cstr::Row& vsyncRow = settingsColumn.addWidget(new cstr::Row( {700, 50}, false));
		cstr::Column& vsyncLabelCol = vsyncRow.addWidget(new cstr::Column( {200, 50}, false));
		std::string vsync = "V-Sync";
		dictionary.get("vsyncLabel", vsync);
		vsyncLabelCol.addWidget(new cstr::Label(vsync + ':', *assets.getFont("../data/fonts/segoeuisl.ttf"), 50));

		vsyncRow.addWidget(new cstr::Spacer( {450, 50}));

		cstr::Column& vsyncToggleCol = vsyncRow.addWidget(new cstr::Column( {50, 50}, false));
		bool vsyncState = false;
		settings.get("vsync", vsyncState);
		vsyncToggleCol.addWidget(new cstr::Toggle( {50, 50}, *assets.getTexture("../data/textures/toggle.png"), {64, 0, 64, 64}, {0, 0, 64, 64}, vsyncState,
		                         [&](bool s)
		{
			settings.set("vsync", s);
			window.setVerticalSyncEnabled(s);
		}));

		settingsColumn.addWidget(new cstr::Spacer( {700, 25}));

		// row for graphics label and button
		cstr::Row& graphicsRow = settingsColumn.addWidget(new cstr::Row( {700, 50}, false));
		cstr::Column& graphicsRowLabelCol = graphicsRow.addWidget(new cstr::Column( {200, 50}, false));
		std::string graphics = "Graphics";
		dictionary.get("graphicsLabel", graphics);
		graphicsRowLabelCol.addWidget(new cstr::Label(graphics + ':', *assets.getFont("../data/fonts/segoeuisl.ttf"), 50));

		graphicsRow.addWidget(new cstr::Spacer( {400, 50}));

		cstr::Column& graphicsRowButtonCol = graphicsRow.addWidget(new cstr::Column( {100, 50}, false));
		graphicsButton = &graphicsRowButtonCol.addWidget(new cstr::Button( {100, 50}, *assets.getTexture("../data/textures/button.png"), [&]()
		{
			unsigned graphicsLevel = 0;
			settings.get("graphics", graphicsLevel);
			std::string graphicsLevelStr = "Low";
			graphicsLevel++;

			switch(graphicsLevel)
			{
				case 0:
					dictionary.get("graphicsLevelLow", graphicsLevelStr);
					graphicsButton->setString(graphicsLevelStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 25);
					break;

				case 1:
					dictionary.get("graphicsLevelMed", graphicsLevelStr);
					graphicsButton->setString(graphicsLevelStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 25);
					break;

				case 2:
					dictionary.get("graphicsLevelHigh", graphicsLevelStr);
					graphicsButton->setString(graphicsLevelStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 25);
					break;

				default:
					graphicsLevel = 0;
					dictionary.get("graphicsLevelLow", graphicsLevelStr);
					graphicsButton->setString(graphicsLevelStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 25);
					break;
			}

			settings.set("graphics", graphicsLevel);
		}));

		// set button to the correct text
		unsigned graphicsLevel = 0;
		settings.get("graphics", graphicsLevel);
		std::string graphicsLevelStr = "Low";

		switch(graphicsLevel)
		{
			case 0:
				dictionary.get("graphicsLevelLow", graphicsLevelStr);
				graphicsButton->setString(graphicsLevelStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 25);
				break;

			case 1:
				dictionary.get("graphicsLevelMed", graphicsLevelStr);
				graphicsButton->setString(graphicsLevelStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 25);
				break;

			case 2:
				dictionary.get("graphicsLevelHigh", graphicsLevelStr);
				graphicsButton->setString(graphicsLevelStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 25);
				break;

			default:
				graphicsLevel = 0;
				dictionary.get("graphicsLevelLow", graphicsLevelStr);
				graphicsButton->setString(graphicsLevelStr, *assets.getFont("../data/fonts/segoeuisl.ttf"), 25);
				break;
		}

		settingsColumn.addWidget(new cstr::Spacer( {700, 25}));

		// row for text entering
		cstr::Row& textEnterRow = settingsColumn.addWidget(new cstr::Row( {700, 50}, false));
		cstr::Column& textEnterLabelCol = textEnterRow.addWidget(new cstr::Column( {200, 50}, false));
		std::string name = "Name";
		dictionary.get("nameLabel", name);
		textEnterLabelCol.addWidget(new cstr::Label(name + ':', *assets.getFont("../data/fonts/segoeuisl.ttf"), 50));

		textEnterRow.addWidget(new cstr::Spacer( {100, 50}));

		cstr::Column& textEnterCol = textEnterRow.addWidget(new cstr::Column( {400, 50}, false));
		textEnterCol.addWidget(new cstr::TextBox( {400, 50}, *assets.getFont("../data/fonts/segoeuisl.ttf"), name));

		settingsColumn.addWidget(new cstr::Spacer( {700, 25}));

		// row for volume slider
		cstr::Row& volumeRow = settingsColumn.addWidget(new cstr::Row( {700, 50}, false));
		cstr::Column& volumeCol = volumeRow.addWidget(new cstr::Column( {200, 50}, false));
		std::string volume = "Volume";
		dictionary.get("volumeLabel", volume);
		volumeCol.addWidget(new cstr::Label(volume + ':', *assets.getFont("../data/fonts/segoeuisl.ttf"), 50));

		volumeRow.addWidget(new cstr::Spacer( {100, 50}));

		cstr::Column& volumeSliderCol = volumeRow.addWidget(new cstr::Column( {400, 50}, false));
		volumeSlider = &volumeSliderCol.addWidget(new cstr::Slider( {400, 50}));

		int sound = 75;
		settings.get("sound", sound);
		volumeSlider->setValue(sound / 100.f);

		settingsColumn.addWidget(new cstr::Spacer( {700, 25}));

		// row for music slider
		cstr::Row& musicRow = settingsColumn.addWidget(new cstr::Row( {700, 50}, false));
		cstr::Column& musicCol = musicRow.addWidget(new cstr::Column( {200, 50}, false));
		std::string musicStr = "Music";
		dictionary.get("musicLabel", musicStr);
		musicCol.addWidget(new cstr::Label(musicStr + ':', *assets.getFont("../data/fonts/segoeuisl.ttf"), 50));

		musicRow.addWidget(new cstr::Spacer( {100, 50}));

		cstr::Column& musicSliderCol = musicRow.addWidget(new cstr::Column( {400, 50}, false));
		musicSlider = &musicSliderCol.addWidget(new cstr::Slider( {400, 50}));

		int music = 75;
		settings.get("music", music);
		musicSlider->setValue(music / 100.f);

		settingsColumn.addWidget(new cstr::Spacer( {700, 25}));

		// row for main menu return
		cstr::Row& mainMenuReturnRow = settingsColumn.addWidget(new cstr::Row( {700, 50}, false));

		mainMenuReturnRow.addWidget(new cstr::Spacer( {600, 50}));

		cstr::Column& mainMenuReturnCol = mainMenuReturnRow.addWidget(new cstr::Column( {100, 50}, false));
		std::string mainMenu = "Main Menu";
		dictionary.get("mainMenuReturn", mainMenu);
		mainMenuReturnCol.addWidget(new cstr::Button( {100, 50}, *assets.getTexture("../data/textures/button.png"), [&]()
		{
			shouldReturn = true;
			states.push(new GameMenu(window, assets, soundPlayer, musicPlayer, settings, dictionary, states, resPath));
		})).setString(mainMenu, *assets.getFont("../data/fonts/segoeuisl.ttf"), 20);
	}
}
