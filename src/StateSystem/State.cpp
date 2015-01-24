#include "State.hpp"

namespace swift
{
	State::State(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic, StateMachine& sm)
	: 	window(win),
		assets(am),
		soundPlayer(sp),
		musicPlayer(mp),
		settings(set),
		dictionary(dic),
		states(sm),
		shouldReturn(false)
	{
	}
	
	State::~State()
	{}
	
	bool State::switchFrom()
	{
		return shouldReturn;
	}
}
