#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Scripting/Script.hpp"

#include "Mapping/TileMap.hpp"

#include "EntitySystem/System.hpp"
#include "EntitySystem/SystemMap.hpp"
#include "EntitySystem/Component.hpp"

namespace swift
{
	class World
	{
		public:
			World(const std::string& n, unsigned int res);
			virtual ~World();

			virtual void update(float dt) = 0;

			bool createEntity(unsigned int id);
			bool destroyEntity(unsigned int id);

			unsigned int getPlayer() const;
			const std::vector<unsigned int>& getEntities() const;
			
			const std::string& getName() const;
			
			const SystemMap& getSystems() const;
			SystemMap& getSystems();
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) = 0;

			TileMap tilemap;

		protected:
			std::vector<unsigned int> entities;
			SystemMap systems;
			
			unsigned int player;
			
			std::vector<Script*> scripts;

		private:
			std::string name;
	};
}

#endif // WORLD_HPP
