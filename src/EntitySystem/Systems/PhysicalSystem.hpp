#ifndef PHYSICALSYSTEM_HPP
#define PHYSICALSYSTEM_HPP

#include "../System.hpp"

namespace swift
{
	class PhysicalSystem : public System
	{
		public:
			virtual void update(Entity& entity, float dt);
	};
}

#endif // PHYSICALSYSTEM_HPP
