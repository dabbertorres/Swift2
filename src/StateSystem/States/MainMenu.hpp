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
			virtual ~MainMenu();

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

#endif // MAINMENU_HPP
