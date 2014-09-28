#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>

#include "Component.hpp"
#include "ComponentRegistry.hpp"

namespace swift
{
	class Entity
	{
		public:
			Entity()
			{

			}

			~Entity()
			{
				auto it = components.begin();
				while(it != components.end())
				{
					if(it->second)
						delete it->second;
					it = components.erase(it);
				}
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
			
			bool add(std::string c)
			{
				if(components.find(c) != components.end())
					return false;
				else
				{
					Component* comp = ComponentRegistry::get(c);
				
					if(comp == nullptr)
						return false;
					
					components.emplace(c, comp);
					return true;
				}
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
			
			bool remove(std::string c)
			{
				if(components.find(c) == components.end())
					return false;
				else
				{
					Component* comp = ComponentRegistry::get(c);
					
					if(comp == nullptr)
						return false;
				
					components.emplace(c, comp);
					return true;
				}
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
			
			// Must be overridden by a Component for it's own type
			/*template<typename C>
			C* get(std::string c)
			{
				if(has(c))
				{
					return static_cast<C*>(components[c]);
				}
				else
					return nullptr;
			}*/
			// not needed for binding
			
			template<typename C>
			bool has() const
			{
				static_assert(std::is_base_of<Component, C>::value, "C must be a child of swift::Component");
				
				return components.find(C::getType()) != components.end();
			}
			
			bool has(std::string c) const
			{
				return components.find(c) != components.end();
			}

		private:
			std::unordered_map<std::string, Component*> components;
	};
}

// Entities can be designed via a simple text file with the following format:
//	Entity
//		Component1
//			type Data
//		Component2
//			type Data1
//			type Data2
// types =
// 	s = string
// 	r = rect
//	f = float
//	i = int

/* Example Entity file
 * Entity
 * 	Drawable
 * 		s ./data/textures/guy.png	# texture
 * 		r 0 0 0 0	# texture rect, if all 0s, use size of texture
 * 	Movable
 * 		f 100	# move velocity
 * 	Physical
 * 		i 400	# x position
 * 		i 300	# y position
 */

#endif // ENTITY_HPP
