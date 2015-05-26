#ifndef MOVABLESYSTEM_HPP
#define MOVABLESYSTEM_HPP

#include "../System.hpp"

#include "../Components/Movable.hpp"

namespace swift
{
	class MovableSystem : public System<Movable>
	{
		public:
			MovableSystem() = default;
			MovableSystem(unsigned int res);
			
			virtual void update(float dt);
	};
}

#endif // MOVABLESYSTEM_HPP
