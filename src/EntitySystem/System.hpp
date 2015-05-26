#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Component.hpp"

#include "../Utility/AssocMap.hpp"

namespace swift
{
	class BaseSystem
	{
		public:
			virtual ~BaseSystem() = default;
			virtual void update(float dt) = 0;
			virtual unsigned int size() const = 0;
			virtual bool has(unsigned int id) const = 0;
			virtual std::vector<const Component*> getAll() const = 0;
			virtual void remove(unsigned int id) = 0;
			virtual void clear() = 0;
			virtual Component::Type typeEnum() const = 0;
	};

	template<typename C, typename std::enable_if<std::is_base_of<Component, C>::value>::type* = nullptr>
	class System : public BaseSystem
	{
		public:
			System() = default;
			
			System(unsigned int res)
			:	components(res)
			{}
			
			virtual ~System() = default;
			
			virtual void update(float dt) = 0;
			
			unsigned int size() const
			{
				return components.size();
			}
			
			bool has(unsigned int id) const
			{
				return components.find(id) != components.key_end();
			}

			C& get(unsigned int id)
			{
				return components.at(id);
			}
			
			std::vector<const Component*> getAll() const
			{
				std::vector<const Component*> comps;
				
				for(auto& c : components)
				{
					comps.push_back(&c);
				}
				
				return comps;
			}
			
			template<typename... Args>
			C* add(unsigned int id, Args&&... args)
			{
				// we pass id twice, first for the key, second for the constructor of the Component
				auto res = components.emplace(id, id, args...);
				
				if(res.second)
				{
					addImpl(*res.first);
					return &*res.first;
				}
				
				return nullptr;
			}
			
			void remove(unsigned int id)
			{
				if(components.find(id) != components.key_end())
				{
					removeImpl(id);
					components.erase(id);
				}
			}
			
			void clear()
			{
				components.clear();
			}
			
			using type = C;
			
			Component::Type typeEnum() const
			{
				return C::type();
			}

		protected:
			util::AssocMap<unsigned int, C> components;
			
		private:
			virtual void addImpl(const C&)
			{}
			
			virtual void removeImpl(unsigned int)
			{}
	};
}

#endif // SYSTEM_HPP
