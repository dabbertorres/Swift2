#ifndef PATHFINDERSYSTEM_HPP
#define PATHFINDERSYSTEM_HPP

#include "../System.hpp"

#include "../Components/Pathfinder.hpp"
#include "../Components/Physical.hpp"
#include "../Components/Movable.hpp"

namespace swift
{
	class World;

	class PathfinderSystem : public System<Pathfinder>
	{
		public:
			PathfinderSystem();

			virtual void update(float dt);

			void setPhysSystem(System<Physical>* ps);
			void setMoveSystem(System<Movable>* ms);

			static World* world;

		private:
			System<Physical>* physSystem;
			System<Movable>* moveSystem;
	};
}

#endif // PATHFINDERSYSTEM_HPP
