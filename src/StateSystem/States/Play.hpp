#ifndef PLAY_HPP
#define PLAY_HPP

#include "../State.hpp"

#include "../SubState.hpp"

#include <vector>

/* GUI headers */
#include "../../GUI/Window.hpp"

/* World headers */
#include "../../World/World.hpp"

/* Scripting */
#include "../../Scripting/Script.hpp"

namespace swift
{
	class Play : public State
	{
		public:
			Play(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic);
			virtual ~Play();

			virtual void setup() = 0;
			virtual void handleEvent(sf::Event& event) = 0;
			virtual void update(sf::Time dt) = 0;
			virtual void draw(float e) = 0;
			bool switchFrom();
			Type finish();

			Entity* getPlayer() const;

			bool addScript(const std::string& scriptFile);
			bool removeScript(const std::string& scriptFile);

			void changeWorld(const std::string& name, const std::string& mapFile);

		protected:
			virtual void setupGUI() = 0;
			virtual void setupSubStates() = 0;
			virtual void setupKeyBindings() = 0;
			
			void loadLastWorld();
			void updateScripts();

			// SubState system
			SubState* activeState;

			cstr::Window hud;
			cstr::Window pauseMenu;

			World* activeWorld;
			Entity* player;
			
			sf::View playView;
			float currentZoom;

		private:
			std::map<std::string, World*> worlds;
			std::map<std::string, Script*> scripts;
	};
}

#endif // PLAY_HPP
