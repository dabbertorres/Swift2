#ifndef THEGAME_HPP
#define THEGAME_HPP

#include "Game.hpp"

#include "StateSystem/StateMachine.hpp"
#include "GameState.hpp"

#include "GameAssets.hpp"

namespace tg
{
	class TheGame : public swift::Game
	{
		public:
			TheGame(int argc, char** argv);
			~TheGame() = default;

		private:
			// loop functions
			virtual void gameHandleEvents(const sf::Event& event);
			virtual void gameUpdate(const sf::Time& dt);
			virtual void manageStates();
			virtual void gameDraw();
			
			// loading functions
			bool loadSettings(const gfs::Path& file);
			void loadAssets();
			void handleArgs(int argc, char** argv);
			
			// init functions
			void initState();
			void initScripting();

			// Sound
			swift::SoundPlayer soundPlayer;
			swift::MusicPlayer musicPlayer;
			
			GameAssets assets;
			
			swift::StateMachine states;
			
			// settings
			unsigned int soundLevel;
			unsigned int musicLevel;
			
			swift::Settings gameSettings;
	};
}

#endif // THEGAME_HPP
