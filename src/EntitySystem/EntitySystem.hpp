#ifndef ENTITY_SYSTEM_HPP
#define ENTITY_SYSTEM_HPP

#include "Entity.hpp"

#include <vector>
#include <string>

namespace swift
{
	class EntitySystem
	{
		public:
			EntitySystem();
			~EntitySystem();

			Entity& create();
			unsigned getSize() const;
			
			std::vector<Entity*>& getEntities();
			
		private:
			std::vector<Entity*> entities;
	};
}

#endif // ENTITY_SYSTEM_HPP
