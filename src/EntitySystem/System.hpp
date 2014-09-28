#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Entity.hpp"

namespace swift
{
	class System
	{
		public:
			virtual ~System() = default;
			virtual void update(Entity& entity, float dt) = 0;
	};
}

#endif // SYSTEM_HPP
