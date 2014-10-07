#ifndef TESTWORLD_HPP
#define TESTWORLD_HPP

#include "../World.hpp"

/* Systems */
#include "../../EntitySystem/Systems/DrawableSystem.hpp"
#include "../../EntitySystem/Systems/MovableSystem.hpp"
#include "../../EntitySystem/Systems/PhysicalSystem.hpp"

namespace swift
{

	class TestWorld : public World
	{
		public:
			TestWorld(const sf::Vector2i s, AssetManager& a);
			virtual ~TestWorld();

			virtual bool load(const std::string& file);
			virtual bool save(const std::string& file);
			virtual void update(float dt);

		private:
			DrawableSystem drawSystem;
			MovableSystem moveSystem;
			PhysicalSystem physicalSystem;
	};

}

#endif // TESTWORLD_HPP
