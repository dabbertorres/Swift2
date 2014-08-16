#include "State.hpp"

namespace swift
{
	State::State(sf::RenderWindow& win, AssetManager& am)
		: 	window(win),
			assets(am)
	{
	}

	State::~State()
	{
	}
}
