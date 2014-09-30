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

namespace swift
{
	class World : public sf::Drawable
	{
		public:
			World(const sf::Vector2i& s, AssetManager& am);
			virtual ~World();

			Entity* addEntity();
			
			bool removeEntity(int e);
			
			const std::vector<Entity*>& getEntities() const;
			
			const std::vector<Entity*>& calculateEntitiesAround(sf::Vector2f pos, float radius);
			
			const std::vector<Entity*>& getEntitiesAround() const;

			virtual void update(float dt) = 0;

			virtual bool load(const std::string& file) = 0;

			virtual bool save(const std::string& file) = 0;

		protected:
			AssetManager& assets;
			
			sf::View view;

			sf::Vector2i size;
			
			std::vector<Entity*> entities;
			
			std::vector<Entity*> entitiesAround;

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

			float distance(sf::Vector2f one, sf::Vector2f two) const;
	};
}

#endif // WORLD_HPP
