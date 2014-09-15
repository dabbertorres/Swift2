#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>

#include "Component.hpp"

namespace swift
{
	class Entity
	{
		public:
			Entity()
			{

			}

			virtual ~Entity()
			{
				for(auto& c : components)
					delete c.second;
			}
			
			template<typename C>
			bool add()
			{
				static_assert(std::is_base_of<Component, C>::value, "C must be a child of swift::Component");
				
				if(!has<C>())
				{
					components.emplace(C::getType(), new C);
					return true;
				}
				else
					return false;
			}
			
			template<typename C>
			bool remove()
			{
				static_assert(std::is_base_of<Component, C>::value, "C must be a child of swift::Component");
				
				if(has<C>())
				{
					delete components[C::getType()];
					components.erase(C::getType());
					return true;
				}
				else
					return false;
			}
			
			template<typename C>
			C* get()
			{
				static_assert(std::is_base_of<Component, C>::value, "C must be a child of swift::Component");
				
				if(has<C>())
				{
					return static_cast<C*>(components[C::getType()]);
				}
				else
					return nullptr;
			}
			
			template<typename C>
			bool has() const
			{
				static_assert(std::is_base_of<Component, C>::value, "C must be a child of swift::Component");
				
				return components.find(C::getType()) != components.end();
			}

		private:
			std::unordered_map<std::string, Component*> components;
	};
}

// Entities can be designed via a simple text file with the following format:
//	Entity
//		Component1
//			Data
//		Component2
//			Data1
//			Data2

/* Example Entity file
 * Entity
 * 	Drawable
 * 		./data/textures/guy.png	# texture
 * 		0 0 0 0	# texture rect, if all 0s, use size of texture
 * 	Movable
 * 		100	# move velocity
 * 	Physical
 * 		400	# x position
 * 		300	# y position
 */

#endif // ENTITY_HPP
