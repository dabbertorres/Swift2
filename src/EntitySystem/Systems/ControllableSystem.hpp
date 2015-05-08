#ifndef CONTROLLABLESYSTEM_HPP
#define CONTROLLABLESYSTEM_HPP

#include "../System.hpp"

#include "../Components/Controllable.hpp"

namespace swift
{
	class ControllableSystem : public System<Controllable>
	{
		public:
			virtual void update(float dt);
	};
}

#endif // CONTROLLABLESYSTEM_HPP
