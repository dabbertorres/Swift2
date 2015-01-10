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
			
			Entity(const Entity& other)
			{
				*this = other;
			}
			
			Entity& operator=(const Entity& other)
			{
				if(other.has<Controllable>())
				{
					add<Controllable>();
					*get<Controllable>() = *other.get<Controllable>();
				}
				
				if(other.has<Drawable>())
				{
					add<Drawable>();
					*get<Drawable>() = *other.get<Drawable>();
				}
				
				if(other.has<Movable>())
				{
					add<Movable>();
					*get<Movable>() = *other.get<Movable>();
				}
				
				if(other.has<Name>())
				{
					add<Name>();
					*get<Name>() = *other.get<Name>();
				}
				
				if(other.has<Noisy>())
				{
					add<Noisy>();
					*get<Noisy>() = *other.get<Noisy>();
				}
				
				if(other.has<Pathfinder>())
				{
					add<Pathfinder>();
					*get<Pathfinder>() = *other.get<Pathfinder>();
				}
				
				if(other.has<Physical>())
				{
					add<Physical>();
					*get<Physical>() = *other.get<Physical>();
				}
				
				return *this;
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
				if(has(c))
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
				if(has(c))
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
			C* get() const
			{
				static_assert(std::is_base_of<Component, C>::value, "C must be a child of swift::Component");
				
				if(has<C>())
				{
					return static_cast<C*>(components.at(C::getType()));
				}
				else
					return nullptr;
			}
			
			Component* get(std::string c) const
			{
				if(has(c))
					return components.at(c);
				else
					return nullptr;
			}
			
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
			
			const std::unordered_map<std::string, Component*>& getComponents() const
			{
				return components;
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
