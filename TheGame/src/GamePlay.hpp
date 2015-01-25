#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "../src/StateSystem/State.hpp"
#include "../src/StateSystem/SubState.hpp"

/* GUI headers */
#include "../src/GUI/Window.hpp"

/* World headers */
#include "../src/World/World.hpp"

/* Scripting */
#include "../src/Scripting/ScriptManager.hpp"
#include "../src/Scripting/Script.hpp"

namespace tg
{
	class GamePlay : public swift::State
	{
		public:
			GamePlay(sf::RenderWindow& win, swift::AssetManager& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic, swift::StateMachine& sm);
			~GamePlay();
			
			virtual void handleEvent(sf::Event& event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);

			swift::Entity* getPlayer() const;

			void changeWorld(const std::string& name, const std::string& mapFile);

		private:
			void loadLastWorld();
			
			void setupGUI();
			void setupSubStates();
			void setupKeyBindings();

			// SubState system
			swift::SubState* activeState;
			swift::SubState play;
			swift::SubState pause;

			cstr::Window hud;
			cstr::Window pauseMenu;

			swift::World* activeWorld;
			swift::Entity* player;
			
			sf::View playView;
			float currentZoom;
			
			swift::ScriptManager scripts;
			
			std::map<std::string, swift::World*> worlds;
	};
}

#endif // GAMEPLAY_HPP