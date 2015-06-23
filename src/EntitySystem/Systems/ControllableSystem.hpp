#ifndef CONTROLLABLESYSTEM_HPP
#define CONTROLLABLESYSTEM_HPP

#include "../System.hpp"

#include "../Components/Controllable.hpp"
#include "../Components/Movable.hpp"

namespace swift
{
	class ControllableSystem : public System<Controllable>
	{
		public:
			ControllableSystem();
			
			virtual void update(float dt);
			
			void setMovableSystem(System<Movable>* ms);
			
		private:
			System<Movable>* moveSystem;
	};
}

#endif // CONTROLLABLESYSTEM_HPP
