#ifndef CONTROLLABLESYSTEM_HPP
#define CONTROLLABLESYSTEM_HPP

#include "../System.hpp" // Base class: swift::System

namespace swift
{
	class ControllableSystem : public swift::System
	{
		public:
			virtual void update(std::vector<Entity*>& entities, float dt);
	};
}

#endif // CONTROLLABLESYSTEM_HPP
