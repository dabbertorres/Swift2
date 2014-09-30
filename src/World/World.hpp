#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Drawable.hpp>

/* Resources */
#include "../ResourceManager/AssetManager.hpp"

/* Entity */
#include "../EntitySystem/Entity.hpp"

/* Systems */
#include "../EntitySystem/Systems/DrawableSystem.hpp"
#include "../EntitySystem/Systems/MovableSystem.hpp"
#include "../EntitySystem/Systems/PhysicalSystem.hpp"

#include "../Mapping/TileMap.hpp"

namespace swift
{
	class World
	{
		public:
			World(const sf::Vector2i& s, AssetManager& am);
			virtual ~World();

			virtual void update(float dt);
			
			virtual void drawWorld(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
			virtual void drawEntities(sf::RenderTarget& target, sf::RenderStates = sf::RenderStates::Default);

			virtual bool load(const std::string& file);
			virtual bool save(const std::string& file);

			Entity* addEntity();
			
			bool removeEntity(int e);
			
			const std::vector<Entity*>& getEntities() const;
			
			const std::vector<Entity*>& calculateEntitiesAround(sf::Vector2f pos, float radius);
			
			const std::vector<Entity*>& getEntitiesAround() const;

			TileMap tilemap;

		protected:
			AssetManager& assets;
			
			sf::View view;

			sf::Vector2i size;

			DrawableSystem drawSystem;
			MovableSystem moveSystem;
			PhysicalSystem physicalSystem;
			
			std::vector<Entity*> entities;
			std::vector<Entity*> entitiesAround;

		private:
			float distance(sf::Vector2f one, sf::Vector2f two) const;
	};
}

#endif // WORLD_HPP
