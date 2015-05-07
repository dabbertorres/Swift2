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
			Entity(unsigned int i)
				:	id(i)
			{}

			Entity(const Entity& other)
			{
				*this = other;
			}

			Entity& operator=(const Entity& other)
			{
				if(other.has<Animated>())
				{
					add<Animated>();
					*get<Animated>() = *other.get<Animated>();
				}

				if(other.has<BatchDrawable>())
				{
					add<BatchDrawable>();
					*get<BatchDrawable>() = *other.get<BatchDrawable>();
				}

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

				id = other.getID();

				return *this;
			}

			~Entity()
			{
				auto it = components.begin();

				while(it != components.end())
				{
					if(it->second)
					{
						delete it->second;
					}

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
				{
					return false;
				}
			}

			bool add(std::string c)
			{
				if(has(c))
				{
					return false;
				}
				else
				{
					Component* comp = ComponentRegistry::get(c);

					if(comp == nullptr)
					{
						return false;
					}

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
				{
					return false;
				}
			}

			bool remove(std::string c)
			{
				if(has(c))
				{
					delete components[c];
					components.erase(c);
					
					return true;
				}
				else
				{
					return false;
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
				{
					return nullptr;
				}
			}

			Component* get(std::string c) const
			{
				if(has(c))
				{
					return components.at(c);
				}
				else
				{
					return nullptr;
				}
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

			unsigned int getID() const
			{
				return id;
			}

		private:
			std::unordered_map<std::string, Component*> components;
			unsigned int id;
	};
}

#endif // ENTITY_HPP
