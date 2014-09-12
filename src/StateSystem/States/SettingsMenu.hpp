#ifndef SETTINGS_MENU_HPP
#define SETTINGS_MENU_HPP

#include "../State.hpp"

#include "../../Settings/Settings.hpp"

/* GUI headers */
#include "../../GUI/Window.hpp"
#include "../../GUI/Widgets/Button.hpp"

namespace swift
{
	class SettingsMenu : public State
	{
		public:
			SettingsMenu(sf::RenderWindow& win, AssetManager& am, Settings& s);
			~SettingsMenu();
			
			virtual void setup();
			virtual void handleEvent(sf::Event &event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);
			virtual bool switchFrom();
			virtual Type finish();

		private:
			cstr::Window gui;
			cstr::Button* graphicsButton;
			Settings& settings;
	};
}

#endif // SETTINGS_MENU_HPP
