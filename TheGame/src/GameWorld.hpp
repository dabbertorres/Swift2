#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "World/World.hpp"

#include "GameAssets.hpp"

namespace tg
{
	class GameWorld : public swift::World
	{
		public:
			GameWorld(const std::string& n, GameAssets* am);

			virtual void update(float dt);
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
			
		private:
			GameAssets* assets;
	};
}

#endif // GAMEWORLD_HPP
