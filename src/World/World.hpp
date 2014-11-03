#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>
#include <map>

/* SFML */
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Drawable.hpp>

/* Resources */
#include "../ResourceManager/AssetManager.hpp"

/* Entity */
#include "../EntitySystem/Entity.hpp"

#include "../EntitySystem/Systems/DrawableSystem.hpp"
#include "../EntitySystem/Systems/MovableSystem.hpp"
#include "../EntitySystem/Systems/PhysicalSystem.hpp"

#include "../Mapping/TileMap.hpp"

namespace swift
{
	class World
	{
		public:
			World(const std::string& n, const sf::Vector2i& s, AssetManager& am);
			virtual ~World();

			virtual void update(float dt);

			virtual bool load();
			virtual bool save();

			void drawWorld(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
			void drawEntities(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

			sf::Vector2i getSize() const;
			
			std::string getName() const;

			Entity* addEntity();
			bool removeEntity(int e);

			bool addScript(const std::string& scriptFile);
			bool removeScript(const std::string& scriptFile);

			const std::vector<Entity*>& getEntities() const;

			const std::vector<Entity*> getEntitiesAround(sf::Vector2f pos, float radius);

			float distance(sf::Vector2f one, sf::Vector2f two) const;

			TileMap tilemap;

		protected:
			AssetManager& assets;
			
			DrawableSystem drawSystem;
			MovableSystem moveSystem;
			PhysicalSystem physicalSystem;

			sf::Vector2i size;

			std::vector<Entity*> entities;

			std::map<std::string, Script*> scripts;

		private:
			std::string name;
	};
}

#endif // WORLD_HPP
