#include "GameMenu.hpp"

#include "ResourceManager/ResourceNotFound.hpp"

/* GUI headers */
#include "GUI/Containers/Column.hpp"
#include "GUI/Containers/Row.hpp"
#include "GUI/Widgets/Label.hpp"
#include "GUI/Widgets/Button.hpp"
#include "GUI/Widgets/Spacer.hpp"

#include "GamePlay.hpp"
#include "GameSettingsMenu.hpp"

namespace tg
{
	GameMenu::GameMenu(sf::RenderWindow& win, GameAssets& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::StateMachine& sm)
		:	GameState(win, am, sp, mp, set, sm)
	{
		window.setKeyRepeatEnabled(true);

		setupGUI();
	}

	void GameMenu::handleEvent(const sf::Event& event)
	{
		gui.update(event);
		keyboard(event);
		mouse(event);
	}
	
	void GameMenu::update(const sf::Time&)
	{
		soundPlayer.update();
		musicPlayer.update();
	}

	void GameMenu::draw()
	{
		window.draw(gui);
	}

	void GameMenu::setupGUI()
	{
		try
		{
			sf::Font& font = assets.getFont("segoeuisl.ttf");
			sf::Texture& buttonTexture = assets.getTexture("button.png");
			
			std::string dictStr = "en";
			
			if(!settings.get("lang", dictStr))
			{
				swift::Logger::get() << "[WARNING]: No language set, defaulting to English (en).\n";
			}
			
			swift::Dictionary& dictionary = assets.getDict(dictStr);
			
			cstr::Column& titleColumn = gui.addContainer(new cstr::Column({300, 0, 200, 600}, false));
			
			titleColumn.addWidget(new cstr::Spacer({200, 100}));
			
			std::string title = "Swift2";
			dictionary.get("titleLabel", title);
			titleColumn.addWidget(new cstr::Label("Swift2", font, 60));
			
			titleColumn.addWidget(new cstr::Spacer({200, 100}));
			
			cstr::Column& buttonColumn = titleColumn.addWidget(new cstr::Column({100, 200}, false));
			
			std::string start = "Start";
			dictionary.get("startButton", start);
			buttonColumn.addWidget(new cstr::Button({100, 50}, buttonTexture, [&]()
			{
				done = true;
				states.push(new GamePlay(window, assets, soundPlayer, musicPlayer, settings, states));
			})).setString(start, font, 25);
			
			buttonColumn.addWidget(new cstr::Spacer({100, 25}));
			
			std::string settingsStr = "Settings";
			dictionary.get("settingsButton", settingsStr);
			buttonColumn.addWidget(new cstr::Button({100, 50}, buttonTexture, [&]()
			{
				states.push(new GameSettingsMenu(window, assets, soundPlayer, musicPlayer, settings, states), false);
			})).setString(settingsStr, font, 25);
			
			buttonColumn.addWidget(new cstr::Spacer({100, 25}));
			
			std::string exit = "Exit";
			dictionary.get("exitButton", exit);
			buttonColumn.addWidget(new cstr::Button({100, 50}, buttonTexture, [&]()
			{
				done = true;
			})).setString(exit, font, 25);
		}
		catch(const swift::ResourceNotFound& rnf)
		{
			swift::Logger::get() << rnf.what() << '\n';
		}
	}
}
