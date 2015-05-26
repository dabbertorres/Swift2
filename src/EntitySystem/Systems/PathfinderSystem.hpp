#ifndef PATHFINDERSYSTEM_HPP
#define PATHFINDERSYSTEM_HPP

#include "../System.hpp"

#include "../Components/Pathfinder.hpp"

namespace swift
{
	class World;

	class PathfinderSystem : public System<Pathfinder>
	{
		public:
			PathfinderSystem() = default;
			PathfinderSystem(unsigned int res);
			
			virtual void update(float dt);

			static World* world;
	};
}

#endif // PATHFINDERSYSTEM_HPP
