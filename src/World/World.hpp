#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>

/* resources */
#include "../ResourceManager/AssetManager.hpp"

/* Entity */
#include "../EntitySystem/Entity.hpp"

/* Component headers */
#include "../EntitySystem/Components/Drawable.hpp"
#include "../EntitySystem/Components/Physical.hpp"
#include "../EntitySystem/Components/Movable.hpp"

/* Systems */
#include "../EntitySystem/Systems/DrawableSystem.hpp"
#include "../EntitySystem/Systems/MovableSystem.hpp"
#include "../EntitySystem/Systems/PhysicalSystem.hpp"

namespace swift
{
	class World
	{
		public:
			World(const sf::Vector2i& s, AssetManager& am);

			std::vector<Entity>& getEntities();

			Entity& addEntity();

			virtual void update(float dt) = 0;
			
			virtual void draw(sf::RenderTarget& target) = 0;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;

			virtual bool load(const std::string& file) = 0;

			virtual bool save(const std::string& file) = 0;

		protected:
			DrawableSystem drawSystem;
			MovableSystem moveSystem;
			PhysicalSystem physicalSystem;
			
			AssetManager& assets;
			
			sf::View view;

			sf::Vector2i size;

		private:
			std::vector<Entity> entities;
	};
}

#endif // WORLD_HPP
