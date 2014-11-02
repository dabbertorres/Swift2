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
			MainMenu(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic);
			~MainMenu();

			virtual void setup();
			virtual void handleEvent(sf::Event &event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);
			virtual bool switchFrom();
			virtual Type finish();

		private:
			cstr::Window gui;
	};
}

#endif // MAINMENU_HPP
