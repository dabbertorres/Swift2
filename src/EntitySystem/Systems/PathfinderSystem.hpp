#ifndef PATHFINDERSYSTEM_HPP
#define PATHFINDERSYSTEM_HPP

#include "../System.hpp"

namespace swift
{
	class World;

	class PathfinderSystem
	{
		public:
			virtual void update(std::vector<Entity*>& entities, float);

			static World* world;
	};
}

#endif // PATHFINDERSYSTEM_HPP
