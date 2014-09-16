#ifndef MAINWORLD_HPP
#define MAINWORLD_HPP

#include "../World.hpp"

namespace swift
{
	class MainWorld : public World
	{
		public:
			MainWorld(const sf::Vector2i& s, AssetManager& am);
			
			virtual void update(float dt);
			
			virtual void draw(sf::RenderTarget& target);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
			
			virtual void load(const std::string& file);
			
			virtual void save(const std::string& file);
	};
}

#endif // MAINWORLD_HPP
