#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>

#include "../EntitySystem/Entity.hpp"

#include "../Mapping/TileMap.hpp"

namespace swift
{
	class World
	{
		public:
			World(const std::string& n);
			virtual ~World() = default;

			virtual void update(float dt) = 0;
			virtual void draw(sf::RenderTarget& target, float e, sf::RenderStates states = sf::RenderStates::Default) = 0;

			Entity* addEntity();
			bool removeEntity(int e);

			Entity* getEntity(int e);
			Entity* getPlayer();
			std::vector<Entity*> getEntities();

			std::vector<Entity*> getEntitiesAround(const sf::Vector2f& pos, float radius);
			std::vector<unsigned> getEntitiesAroundIDs(const sf::Vector2f& pos, float radius);

			const std::string& getName() const;

			TileMap tilemap;

		protected:
			std::vector<Entity> entities;

		private:
			std::string name;
	};
}

#endif // WORLD_HPP
