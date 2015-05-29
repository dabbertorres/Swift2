#include "GameState.hpp"

namespace tg
{
	GameState::GameState(sf::RenderWindow& win, GameAssets& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic, swift::StateMachine& sm)
	:	window(win),
		assets(am),
		soundPlayer(sp),
		musicPlayer(mp),
		settings(set),
		dictionary(dic),
		states(sm)
	{}
}
