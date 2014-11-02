#include "State.hpp"

namespace swift
{
	State::State(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic)
		: 	window(win),
			assets(am),
			soundPlayer(sp),
			musicPlayer(mp),
			settings(set),
			dictionary(dic)
	{
	}

	State::~State()
	{
	}
}
