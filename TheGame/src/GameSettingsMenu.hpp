#ifndef GAMESETTINGS_HPP
#define GAMESETTINGS_HPP

#include "GameState.hpp"

#include "KeyBindings/KeyboardManager.hpp"
#include "KeyBindings/MouseManager.hpp"

/* GUI headers */
#include "GUI/Window.hpp"
#include "GUI/Widgets/Button.hpp"
#include "GUI/Widgets/Slider.hpp"

namespace tg
{
	class GameSettings : public GameState
	{
		public:
			GameSettings(sf::RenderWindow& win, GameAssets& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic, swift::StateMachine& sm);

			virtual void handleEvent(const sf::Event& event);
			virtual void update(const sf::Time& dt);
			virtual void draw();

		private:
			void setupGUI();

			cstr::Window gui;

			cstr::Button* graphicsButton;
			cstr::Slider* volumeSlider;
			cstr::Slider* musicSlider;
			
			swift::KeyboardManager keyboard;
			swift::MouseManager mouse;
	};
}

#endif // GAMESETTINGS_HPP
