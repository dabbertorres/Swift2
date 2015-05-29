#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "GameState.hpp"

#include "StateSystem/SubState.hpp"

#include "GUI/Window.hpp"

#include "KeyBindings/KeyboardManager.hpp"
#include "KeyBindings/MouseManager.hpp"

#include "GameWorld.hpp"

#include "Scripting/ScriptManager.hpp"
#include "Scripting/Script.hpp"

namespace tg
{
	class GamePlay : public GameState
	{
		public:
			GamePlay(sf::RenderWindow& win, GameAssets& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic, swift::StateMachine& sm);
			~GamePlay();

			virtual void handleEvent(const sf::Event& event);
			virtual void update(const sf::Time& dt);
			virtual void draw();

			unsigned int getPlayer() const;

			void changeWorld(const std::string& name, const std::string& mapFile);

		private:
			void loadLastWorld();

			bool loadWorld(swift::World& world);
			bool saveWorld(swift::World& world);

			void setupGUI();
			void setupSubStates();
			void setupKeyBindings();

			// SubState system
			swift::SubState* activeState;
			swift::SubState play;
			swift::SubState pause;
			
			// GUI
			cstr::Window hud;
			cstr::Window pauseMenu;
			
			// input
			swift::KeyboardManager keyboard;
			swift::MouseManager mouse;
			
			// world
			GameWorld* activeWorld;

			sf::View playView;
			float currentZoom;

			std::map<std::string, GameWorld*> worlds;
			
			// scripting
			swift::ScriptManager scripts;
	};
}

#endif // GAMEPLAY_HPP
