#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Component.hpp"

namespace swift
{
	class Entity
	{
		public:
			Entity();
			~Entity();
			
			void add(Component& c);

	};
}

#endif // ENTITY_HPP
