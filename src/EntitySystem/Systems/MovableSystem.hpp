#ifndef MOVABLESYSTEM_HPP
#define MOVABLESYSTEM_HPP

#include "../System.hpp"

#include "../Components/Movable.hpp"
#include "../Components/Physical.hpp"

namespace swift
{
	class MovableSystem : public System<Movable>
	{
		public:
			MovableSystem();
		
			virtual void update(float dt);
			
			void setPhysicalSystem(System<Physical>* ps);
			
		private:
			System<Physical>* physSystem;
	};
}

#endif // MOVABLESYSTEM_HPP
