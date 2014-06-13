#ifndef SETTINGS_MENU_HPP
#define SETTINGS_MENU_HPP

#include "../State.hpp"

namespace swift
{
	class SettingsMenu : public State
	{
		public:
			SettingsMenu(sf::RenderWindow& win, AssetManager& am);
			~SettingsMenu();
			
			virtual void setup();
			virtual void handleEvent(sf::Event &event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);
			virtual bool switchFrom();
			virtual Type finish();

		private:
			void setupButtons();
			
			cstr::Window gui;
	};
}

#endif // SETTINGS_MENU_HPP
