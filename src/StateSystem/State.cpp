#include "State.hpp"

namespace swift
{
	State::State(sf::RenderWindow& win, AssetManager& am, Settings& set, Settings& dic)
		: 	window(win),
			assets(am),
			settings(set),
			dictionary(dic)
	{
	}

	State::~State()
	{
	}
}
