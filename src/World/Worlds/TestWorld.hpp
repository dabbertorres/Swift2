#ifndef MAINWORLD_HPP
#define MAINWORLD_HPP

#include "../World.hpp"

#include "../../Mapping/TileMap.hpp"

/* Component headers */
#include "../../EntitySystem/Components/Drawable.hpp"
#include "../../EntitySystem/Components/Physical.hpp"
#include "../../EntitySystem/Components/Movable.hpp"

/* Systems */
#include "../../EntitySystem/Systems/DrawableSystem.hpp"
#include "../../EntitySystem/Systems/MovableSystem.hpp"
#include "../../EntitySystem/Systems/PhysicalSystem.hpp"

namespace swift
{
	class TestWorld : public World
	{
		public:
			TestWorld(const sf::Vector2i& s, AssetManager& am);
			virtual ~TestWorld() = default;

			virtual void update(float dt);

			virtual bool load(const std::string& file);

			virtual bool save(const std::string& file);

			TileMap tilemap;

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			DrawableSystem drawSystem;
			MovableSystem moveSystem;
			PhysicalSystem physicalSystem;
	};
}

#endif // MAINWORLD_HPP
