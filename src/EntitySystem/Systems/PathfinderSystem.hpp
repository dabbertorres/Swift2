#ifndef PATHFINDERSYSTEM_HPP
#define PATHFINDERSYSTEM_HPP

#include "../System.hpp"

namespace swift
{
	class PathfinderSystem
	{
		public:
			virtual void update(std::vector<Entity*>& entities, float);
	};
}

#endif // PATHFINDERSYSTEM_HPP
