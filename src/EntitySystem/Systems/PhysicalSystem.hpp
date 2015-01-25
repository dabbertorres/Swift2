#ifndef PHYSICALSYSTEM_HPP
#define PHYSICALSYSTEM_HPP

#include "../System.hpp"

#include "../../Collision/Collision.hpp"

#include <vector>

namespace swift
{
	class Collision;
	
	class PhysicalSystem : public System
	{
		public:
			virtual void update(const std::vector<Entity>& entities, float dt);
			
			const std::vector<Collision>& getCollisions() const;
			
		private:
			std::vector<Collision> collisions;
	};
}

#endif // PHYSICALSYSTEM_HPP
