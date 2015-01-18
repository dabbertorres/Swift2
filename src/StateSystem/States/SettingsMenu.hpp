#ifndef SETTINGS_MENU_HPP
#define SETTINGS_MENU_HPP

#include "../State.hpp"

#include "../../Settings/Settings.hpp"

/* GUI headers */
#include "../../GUI/Window.hpp"
#include "../../GUI/Widgets/Button.hpp"
#include "../../GUI/Widgets/Slider.hpp"

namespace swift
{
	class SettingsMenu : public State
	{
		public:
			SettingsMenu(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic);
			virtual ~SettingsMenu();
			
			virtual void setup() = 0;
			virtual void handleEvent(sf::Event &event) = 0;
			virtual void update(sf::Time dt) = 0;
			virtual void draw(float e) = 0;
			
			virtual bool switchFrom();
			Type finish();

		protected:
			cstr::Window gui;
	};
}

#endif // SETTINGS_MENU_HPP
