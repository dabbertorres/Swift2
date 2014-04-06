#ifndef ENTITY_SYSTEM_HPP
#define ENTITY_SYSTEM_HPP

#include "Entity.hpp"

#include <map>
#include <string>

namespace swift
{
	class EntitySystem
	{
		public:
			EntitySystem();
			~EntitySystem();

			Entity& create();
			bool has(unsigned id);
			
			Entity& get(unsigned id);
			std::map<unsigned, Entity>& getEntities();
			
		private:
			std::map<unsigned, Entity> entities;
	};
}

#endif // ENTITY_SYSTEM_HPP
