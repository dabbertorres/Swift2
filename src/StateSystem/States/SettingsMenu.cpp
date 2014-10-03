#include "SettingsMenu.hpp"

#include "../../ResourceManager/AssetManager.hpp"

/* GUI headers */
#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Spacer.hpp"
#include "../../GUI/Widgets/Slider.hpp"
#include "../../GUI/Widgets/Toggle.hpp"
#include "../../GUI/Widgets/TextBox.hpp"

namespace swift
{
	SettingsMenu::SettingsMenu(sf::RenderWindow& win, AssetManager& am, Settings& set, Settings& dic)
		:	State(win, am, set, dic)
	{
		returnType = State::Type::SettingsMenu;
	}

	SettingsMenu::~SettingsMenu()
	{
	}

	void SettingsMenu::setup()
	{
		window.setKeyRepeatEnabled(true);
		Script* setup = &assets.getScript("./data/scripts/settingsMenu.lua");
		
		setup->setGUI(gui);
		setup->setStateReturn(returnType);
		setup->start();
		
		cstr::Column& settingsColumn = gui.addContainer(new cstr::Column({50, 25, 700, 550}, false));
		
		std::string settingsStr = "Settings";
		dictionary.get("settingsLabel", settingsStr);
		cstr::Column& titleCol = settingsColumn.addWidget(new cstr::Column({200, 50}, false));
		titleCol.addWidget(new cstr::Label(settingsStr, assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for fullscreen label and toggle
		cstr::Row& fullscreenRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		cstr::Column& fullscreenLabelCol = fullscreenRow.addWidget(new cstr::Column({200, 50}, false));
		std::string fullscreen = "Fullscreen";
		dictionary.get("fullscreenLabel", fullscreen);
		fullscreenLabelCol.addWidget(new cstr::Label(fullscreen + ':', assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		fullscreenRow.addWidget(new cstr::Spacer({450, 50}));
		
		cstr::Column& fullscreenToggleCol = fullscreenRow.addWidget(new cstr::Column({50, 50}, false));
		bool fullscreenState = false;
		settings.get("fullscreen", fullscreenState);
		fullscreenToggleCol.addWidget(new cstr::Toggle({50, 50}, assets.getTexture("./data/textures/toggleOn.png"), assets.getTexture("./data/textures/toggleOff.png"), fullscreenState, 
		[&](bool s)
		{
			settings.set("fullscreen", s);
			if(s)
			{
				unsigned resx = 0;
				unsigned resy = 0;
				settings.get("res.x", resx);
				settings.get("res.y", resy);
				window.create({resx, resy, 32}, "Swift2", sf::Style::Fullscreen);
			}
			else
			{
				unsigned resx = 800;
				unsigned resy = 600;
				settings.get("res.x", resx);
				settings.get("res.y", resy);
				window.create({resx, resy, 32}, "Swift2", sf::Style::Titlebar | sf::Style::Close);
			}
		}));
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for vsync label and toggle
		cstr::Row& vsyncRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		cstr::Column& vsyncLabelCol = vsyncRow.addWidget(new cstr::Column({200, 50}, false));
		std::string vsync = "V-Sync";
		dictionary.get("vsyncLabel", vsync);
		vsyncLabelCol.addWidget(new cstr::Label(vsync + ':', assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		vsyncRow.addWidget(new cstr::Spacer({450, 50}));
		
		cstr::Column& vsyncToggleCol = vsyncRow.addWidget(new cstr::Column({50, 50}, false));
		bool vsyncState = false;
		settings.get("vsync", vsyncState);
		vsyncToggleCol.addWidget(new cstr::Toggle({50, 50}, assets.getTexture("./data/textures/toggleOn.png"), assets.getTexture("./data/textures/toggleOff.png"), vsyncState,
		[&](bool s)
		{
			settings.set("vsync", s);
			window.setVerticalSyncEnabled(s);
		}));
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for graphics label and button
		cstr::Row& graphicsRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		cstr::Column& graphicsRowLabelCol = graphicsRow.addWidget(new cstr::Column({200, 50}, false));
		std::string graphics = "Graphics";
		dictionary.get("graphicsLabel", graphics);
		graphicsRowLabelCol.addWidget(new cstr::Label(graphics + ':', assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		graphicsRow.addWidget(new cstr::Spacer({400, 50}));
		
		cstr::Column& graphicsRowButtonCol = graphicsRow.addWidget(new cstr::Column({100, 50}, false));
		graphicsButton = &graphicsRowButtonCol.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			unsigned graphicsLevel = 0;
			settings.get("graphics", graphicsLevel);
			std::string graphicsLevelStr = "Low";
			graphicsLevel++;
			switch(graphicsLevel)
			{
				case 0:
					dictionary.get("graphicsLevelLow", graphicsLevelStr);
					graphicsButton->setString(graphicsLevelStr, assets.getFont("./data/fonts/segoeuisl.ttf"));
					break;
				case 1:
					dictionary.get("graphicsLevelMed", graphicsLevelStr);
					graphicsButton->setString(graphicsLevelStr, assets.getFont("./data/fonts/segoeuisl.ttf"));
					break;
				case 2:
					dictionary.get("graphicsLevelHigh", graphicsLevelStr);
					graphicsButton->setString(graphicsLevelStr, assets.getFont("./data/fonts/segoeuisl.ttf"));
					break;
				default:
					graphicsLevel = 0;
					dictionary.get("graphicsLevelLow", graphicsLevelStr);
					graphicsButton->setString(graphicsLevelStr, assets.getFont("./data/fonts/segoeuisl.ttf"));
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
				graphicsButton->setString(graphicsLevelStr, assets.getFont("./data/fonts/segoeuisl.ttf"));
				break;
			case 1:
				dictionary.get("graphicsLevelMed", graphicsLevelStr);
				graphicsButton->setString(graphicsLevelStr, assets.getFont("./data/fonts/segoeuisl.ttf"));
				break;
			case 2:
				dictionary.get("graphicsLevelHigh", graphicsLevelStr);
				graphicsButton->setString(graphicsLevelStr, assets.getFont("./data/fonts/segoeuisl.ttf"));
				break;
			default:
				graphicsLevel = 0;
				dictionary.get("graphicsLevelLow", graphicsLevelStr);
				graphicsButton->setString(graphicsLevelStr, assets.getFont("./data/fonts/segoeuisl.ttf"));
				break;
		}
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for text entering
		cstr::Row& textEnterRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		cstr::Column& textEnterLabelCol = textEnterRow.addWidget(new cstr::Column({200, 50}, false));
		std::string name = "Name";
		dictionary.get("nameLabel", name);
		textEnterLabelCol.addWidget(new cstr::Label(name + ':', assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		textEnterRow.addWidget(new cstr::Spacer({100, 50}));
		
		cstr::Column& textEnterCol = textEnterRow.addWidget(new cstr::Column({400, 50}, false));
		textEnterCol.addWidget(new cstr::TextBox({400, 50}, assets.getFont("./data/fonts/segoeuisl.ttf"), name));
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for volume slider
		cstr::Row& volumeRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		cstr::Column& volumeCol = volumeRow.addWidget(new cstr::Column({200, 50}, false));
		std::string volume = "Volume";
		dictionary.get("volumeLabel", volume);
		volumeCol.addWidget(new cstr::Label(volume + ':', assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		volumeRow.addWidget(new cstr::Spacer({100, 50}));
		
		cstr::Column& volumeSliderCol = volumeRow.addWidget(new cstr::Column({400, 50}, false));
		volumeSlider = &volumeSliderCol.addWidget(new cstr::Slider({400, 50}));
		
		int sound = 75;
		settings.get("sound", sound);
		volumeSlider->setValue(sound / 100.f);
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for music slider
		cstr::Row& musicRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		cstr::Column& musicCol = musicRow.addWidget(new cstr::Column({200, 50}, false));
		std::string musicStr = "Music";
		dictionary.get("musicLabel", musicStr);
		musicCol.addWidget(new cstr::Label(musicStr + ':', assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		musicRow.addWidget(new cstr::Spacer({100, 50}));
		
		cstr::Column& musicSliderCol = musicRow.addWidget(new cstr::Column({400, 50}, false));
		musicSlider = &musicSliderCol.addWidget(new cstr::Slider({400, 50}));
		
		int music = 75;
		settings.get("music", music);
		musicSlider->setValue(music / 100.f);
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for main menu return
		cstr::Row& mainMenuReturnRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		
		mainMenuReturnRow.addWidget(new cstr::Spacer({600, 50}));
		
		cstr::Column& mainMenuReturnCol = mainMenuReturnRow.addWidget(new cstr::Column({100, 50}, false));
		std::string mainMenu = "Main Menu";
		dictionary.get("mainMenuReturn", mainMenu);
		mainMenuReturnCol.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::MainMenu;
		})).setString(mainMenu, assets.getFont("./data/fonts/segoeuisl.ttf"));
	}
	
	void SettingsMenu::handleEvent(sf::Event &event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void SettingsMenu::update(sf::Time /*dt*/)
	{
		Script* setup = &assets.getScript("./data/scripts/settingsMenu.lua");
		
		setup->run();
		
		int sound = volumeSlider->getValue() * 100;
		settings.set("sound", sound);
		
		int music = musicSlider->getValue() * 100;
		settings.set("music", music);
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
}
