#ifndef PLAY_HPP
#define PLAY_HPP

#include "../State.hpp"

#include "../SubState.hpp"

#include <vector>

/* GUI headers */
#include "../../GUI/Window.hpp"

/* World headers */
#include "../../World/World.hpp"

namespace swift
{
	class Play : public State
	{
		public:
			Play(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic);
			~Play();

			virtual void setup();
			virtual void handleEvent(sf::Event& event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);
			virtual bool switchFrom();
			virtual Type finish();
			
			Entity* getPlayer() const;
			
			bool addScript(const std::string& scriptFile);
			bool removeScript(const std::string& scriptFile);
			
			void changeWorld(const std::string& name, const std::string& mapFile);

		private:
			void setupGUI();
			void setupKeyBindings();
			
			// SubState system
			SubState* activeState;
			SubState play;
			SubState pause;

			cstr::Window hud;
			cstr::Window pauseMenu;
			
			sf::View playView;
			float currentZoom;
			
			std::map<std::string, World*> worlds;
			std::map<std::string, Script*> scripts;
			
			World* activeWorld;
			Entity* player;
	};
}

#endif // PLAY_HPP
