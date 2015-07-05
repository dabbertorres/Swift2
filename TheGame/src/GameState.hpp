#ifndef TG_GAME_STATE
#define TG_GAME_STATE

#include "StateSystem/State.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameAssets.hpp"
#include "SoundSystem/SoundPlayer.hpp"
#include "SoundSystem/MusicPlayer.hpp"
#include "Settings/Settings.hpp"
#include "StateSystem/StateMachine.hpp"

namespace tg
{
	class GameState : public swift::State
	{
		public:
			GameState(sf::RenderWindow& win, GameAssets& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::StateMachine& sm);
			virtual ~GameState() = default;
			
			virtual void handleEvent(const sf::Event& event) = 0;
			virtual void update(const sf::Time& dt) = 0;
			virtual void draw() = 0;
			
		protected:
			sf::RenderWindow& window;
			GameAssets& assets;
			swift::SoundPlayer& soundPlayer;
			swift::MusicPlayer& musicPlayer;
			swift::Settings& settings;
			swift::StateMachine& states;
	};
}

#endif // TG_GAME_STATE
