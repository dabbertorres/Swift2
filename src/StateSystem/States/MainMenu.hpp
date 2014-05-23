#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "../State.hpp"

/* GUI headers */
#include "../../GUI/Window.hpp"

namespace swift
{
	class MainMenu : public State
	{
		public:
			MainMenu(sf::RenderWindow& win, AssetManager& am, sf::Font& font);
			~MainMenu();

			virtual void setup();
			virtual void switchTo();
			virtual void handleEvent(sf::Event &event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);
			virtual Type switchFrom();
			virtual void finish();

		private:
			cstr::Window gui;
	};
}

#endif // MAINMENU_HPP
