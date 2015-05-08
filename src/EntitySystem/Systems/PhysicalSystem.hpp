#ifndef PHYSICALSYSTEM_HPP
#define PHYSICALSYSTEM_HPP

#include "../System.hpp"

#include "../Components/Physical.hpp"

#include "../../Collision/Collision.hpp"

#include <vector>

namespace swift
{
	class Collision;
	
	class PhysicalSystem : public System<Physical>
	{
		public:
			virtual void update(float dt);
			
			const std::vector<Collision>& getCollisions() const;
			
		private:
			std::vector<Collision> collisions;
	};
}

#endif // PHYSICALSYSTEM_HPP
