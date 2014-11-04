#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Entity.hpp"

namespace swift
{
	class System
	{
		public:
			virtual ~System() = default;
			virtual void update(const std::vector<Entity*>& entities, float dt) = 0;
	};
}

#endif // SYSTEM_HPP
