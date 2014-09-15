#include "SettingsMenu.hpp"

#include "../../ResourceManager/AssetManager.hpp"

/* GUI headers */
#include "../../GUI/Containers/Column.hpp"
#include "../../GUI/Containers/Row.hpp"
#include "../../GUI/Widgets/Label.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Spacer.hpp"
#include "../../GUI/Widgets/Toggle.hpp"
#include "../../GUI/Widgets/TextBox.hpp"

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
		window.setKeyRepeatEnabled(true);
		Script* setup = &assets.getScript("./data/scripts/settingsMenu.lua");
		
		setup->setGUI(gui);
		setup->setStateReturn(returnType);
		setup->start();
		
		cstr::Column& settingsColumn = gui.addContainer(new cstr::Column({50, 50, 700, 500}, false));
		
		cstr::Column& titleCol = settingsColumn.addWidget(new cstr::Column({200, 50}, false));
		titleCol.addWidget(new cstr::Label("Settings", assets.getFont("./data/fonts/segoeuisl.ttf")));
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for fullscreen label and toggle
		cstr::Row& fullscreenRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		cstr::Column& fullscreenLabelCol = fullscreenRow.addWidget(new cstr::Column({200, 50}, false));
		fullscreenLabelCol.addWidget(new cstr::Label("Fullscreen:", assets.getFont("./data/fonts/segoeuisl.ttf")));
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
				settings.get("resx", resx);
				settings.get("resy", resy);
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
		vsyncLabelCol.addWidget(new cstr::Label("V-Sync:", assets.getFont("./data/fonts/segoeuisl.ttf")));
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
		graphicsRowLabelCol.addWidget(new cstr::Label("Graphics:", assets.getFont("./data/fonts/segoeuisl.ttf")));
		graphicsRow.addWidget(new cstr::Spacer({400, 50}));
		cstr::Column& graphicsRowButtonCol = graphicsRow.addWidget(new cstr::Column({100, 50}, false));
		graphicsButton = &graphicsRowButtonCol.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			unsigned graphicsLevel = 0;
			settings.get("graphics", graphicsLevel);
			graphicsLevel++;
			switch(graphicsLevel)
			{
				case 0:
					graphicsButton->setString("Low", assets.getFont("./data/fonts/segoeuisl.ttf"));
					break;
				case 1:
					graphicsButton->setString("Medium", assets.getFont("./data/fonts/segoeuisl.ttf"));
					break;
				case 2:
					graphicsButton->setString("High", assets.getFont("./data/fonts/segoeuisl.ttf"));
					break;
				default:
					graphicsLevel = 0;
					graphicsButton->setString("Low", assets.getFont("./data/fonts/segoeuisl.ttf"));
					break;
			}
			settings.set("graphics", graphicsLevel);
		}));
		// set button to the correct text
		unsigned graphicsLevel = 0;
		settings.get("graphics", graphicsLevel);
		switch(graphicsLevel)
		{
			case 0:
				graphicsButton->setString("Low", assets.getFont("./data/fonts/segoeuisl.ttf"));
				break;
			case 1:
				graphicsButton->setString("Medium", assets.getFont("./data/fonts/segoeuisl.ttf"));
				break;
			case 2:
				graphicsButton->setString("High", assets.getFont("./data/fonts/segoeuisl.ttf"));
				break;
			default:
				graphicsLevel = 0;
				graphicsButton->setString("Low", assets.getFont("./data/fonts/segoeuisl.ttf"));
				break;
		}
		
		settingsColumn.addWidget(new cstr::Spacer({700, 25}));
		
		// row for text entering
		cstr::Row& textEnterRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		cstr::Column& textEnterLabelCol = textEnterRow.addWidget(new cstr::Column({200, 50}, false));
		textEnterLabelCol.addWidget(new cstr::Label("Name:", assets.getFont("./data/fonts/segoeuisl.ttf")));
		textEnterRow.addWidget(new cstr::Spacer({100, 50}));
		cstr::Column& textEnterCol = textEnterRow.addWidget(new cstr::Column({400, 50}, false));
		textEnterCol.addWidget(new cstr::TextBox({400, 50}, assets.getFont("./data/fonts/segoeuisl.ttf"), "name"));
		
		settingsColumn.addWidget(new cstr::Spacer({700, 100}));
		
		// row for main menu return
		cstr::Row& mainMenuReturnRow = settingsColumn.addWidget(new cstr::Row({700, 50}, false));
		mainMenuReturnRow.addWidget(new cstr::Spacer({600, 50}));
		cstr::Column& mainMenuReturnCol = mainMenuReturnRow.addWidget(new cstr::Column({100, 50}, false));
		mainMenuReturnCol.addWidget(new cstr::Button({100, 50}, assets.getTexture("./data/textures/button.png"), [&]()
		{
			returnType = State::Type::MainMenu;
		})).setString("Main Menu", assets.getFont("./data/fonts/segoeuisl.ttf"));
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
