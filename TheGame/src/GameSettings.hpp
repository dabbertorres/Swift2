#ifndef GAMESETTINGS_HPP
#define GAMESETTINGS_HPP

#include "../src/StateSystem/State.hpp"

/* GUI headers */
#include "../src/GUI/Window.hpp"
#include "../src/GUI/Widgets/Button.hpp"
#include "../src/GUI/Widgets/Slider.hpp"

namespace tg
{
	class GameSettings : public swift::State
	{
		public:
			GameSettings(sf::RenderWindow& win, swift::AssetManager& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set,
			             swift::Settings& dic, swift::StateMachine& sm, const std::string& rs);

			virtual void handleEvent(sf::Event& event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);

		private:
			void setupGUI();

			cstr::Window gui;

			cstr::Button* graphicsButton;
			cstr::Slider* volumeSlider;
			cstr::Slider* musicSlider;
	};
}

#endif // GAMESETTINGS_HPP
