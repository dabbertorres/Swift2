#ifndef PLAY_HPP
#define PLAY_HPP

#include "../State.hpp"

namespace swift
{
	class Play : public State
	{
		public:
			Play(sf::RenderWindow& win);
			~Play();
			
			virtual void handleEvents();
			virtual void update();
			virtual void draw(float i);
	};
}

#endif // PLAY_HPP
