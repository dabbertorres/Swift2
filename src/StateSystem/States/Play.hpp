#ifndef PLAY_HPP
#define PLAY_HPP

#include "../State.hpp"

namespace swift
{
	class Play : public State
	{
		public:
			Play(sf::RenderWindow& win, AssetManager& am);
			~Play();
			
			virtual void setup();
			virtual void switchTo();
			virtual void handleEvent(sf::Event &event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);
			virtual void switchFrom();
			virtual void finish();
	};
}

#endif // PLAY_HPP
