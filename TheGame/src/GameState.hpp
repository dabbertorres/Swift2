#ifndef TG_GAME_STATE
#define TG_GAME_STATE

#include "../../src/StateSystem/State.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include "GameAssets.hpp"
#include "../../src/SoundSystem/SoundPlayer.hpp"
#include "../../src/SoundSystem/MusicPlayer.hpp"
#include "../../src/Settings/Settings.hpp"
#include "../../src/StateSystem/StateMachine.hpp"

namespace tg
{
	class GameState : public swift::State
	{
		public:
			GameState(sf::RenderWindow& win, GameAssets& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic, swift::StateMachine& sm);
			virtual ~GameState() = default;
			
			virtual void handleEvent(const sf::Event& event) = 0;
			virtual void update(const sf::Time& dt) = 0;
			virtual void draw() = 0;
			
		protected:
			sf::RenderWindow& window;
			GameAssets& assets;
			swift::SoundPlayer& soundPlayer;
			swift::MusicPlayer& musicPlayer;
			swift::Settings settings;
			swift::Settings dictionary;
			swift::StateMachine& states;
	};
}

#endif // TG_GAME_STATE
