#ifndef MOVABLESYSTEM_HPP
#define MOVABLESYSTEM_HPP

#include "../System.hpp"

#include "../Entity.hpp"

namespace swift
{
	class MovableSystem : public System
	{
		public:
			void update(Entity& entity, float dt);
	};
}

#endif // MOVABLESYSTEM_HPP
