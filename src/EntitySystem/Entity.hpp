#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include "Component.hpp"

namespace swift
{
	class Entity
	{
		public:
			Entity();
			~Entity();
			
			bool has(unsigned id);
			
			void addID(unsigned id);

		private:
			std::vector<unsigned> components;
	};
}

#endif // ENTITY_HPP
