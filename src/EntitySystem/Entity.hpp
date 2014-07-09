#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cassert>
#include <map>

#include "../../Collision/SeparatingAxisTheorem.hpp"

namespace swift
{
	class Entity
	{
		public:
			Entity();
			virtual ~Entity();
	};
}

#endif // ENTITY_HPP
