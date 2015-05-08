#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>
#include <map>
//#include "../Utility/AssocMap.hpp"

#include "../Mapping/TileMap.hpp"

#include "../EntitySystem/System.hpp"
#include "../EntitySystem/Component.hpp"

namespace swift
{
	class World
	{
		public:
			World(const std::string& n);
			virtual ~World() = default;

			virtual void update(float dt) = 0;
			virtual void draw(sf::RenderTarget& target, float e, sf::RenderStates states = sf::RenderStates::Default) = 0;

			void createEntity(unsigned int id, std::underlying_type<Component::Type>::type t);
			
			bool destroyEntity(int e);

			unsigned int getPlayer() const;
			
			const std::vector<unsigned int>& getEntities() const;

			std::vector<unsigned int> getEntitiesAround(const sf::Vector2f& pos, float radius) const;

			const std::string& getName() const;

			TileMap tilemap;

		protected:
			std::vector<unsigned int> entities;
			unsigned int player;

		private:
			std::string name;
	};
}

#endif // WORLD_HPP
