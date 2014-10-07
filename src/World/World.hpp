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

#include "../Mapping/TileMap.hpp"

#include <map>

namespace swift
{
	class World
	{
		public:
			World(const sf::Vector2i& s, AssetManager& am);
			virtual ~World();

			virtual void update(float dt) = 0;

			virtual bool load(const std::string& file) = 0;
			virtual bool save(const std::string& file) = 0;
			
			void drawWorld(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
			void drawEntities(sf::RenderTarget& target, sf::RenderStates = sf::RenderStates::Default);
			
			sf::Vector2i getSize() const;

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

			sf::Vector2i size;
			
			std::vector<Entity*> entities;
			
			std::map<std::string, Script*> scripts;
	};
}

#endif // WORLD_HPP
