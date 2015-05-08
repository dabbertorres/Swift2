#ifndef MOVABLESYSTEM_HPP
#define MOVABLESYSTEM_HPP

#include "../System.hpp"

#include "../Components/Movable.hpp"

namespace swift
{
	class MovableSystem : public System<Movable>
	{
		public:
			virtual void update(float dt);
	};
}

#endif // MOVABLESYSTEM_HPP
