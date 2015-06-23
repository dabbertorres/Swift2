#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Component.hpp"

#include <google/dense_hash_map>
//#include "../Utility/AssocMap.hpp"

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
			System()
			{
				components.set_empty_key(-1);
				components.set_deleted_key(-2);
			}
			
			virtual ~System() = default;
			
			virtual void update(float dt) = 0;
			
			unsigned int size() const
			{
				return components.size();
			}
			
			bool has(unsigned int id) const
			{
				return components.find(id) != components.end();
			}

			C& get(unsigned int id)
			{
				return components[id];
			}
			
			std::vector<const Component*> getAll() const
			{
				std::vector<const Component*> comps;
				
				for(auto& c : components)
				{
					comps.push_back(&c.second);
				}
				
				return comps;
			}
			
			template<typename... Args>
			C* add(unsigned int id, Args&&... args)
			{
				auto res = components.insert(std::make_pair(id, C(id, args...)));
				
				if(res.second)
				{
					addImpl(res.first->second);
					return &res.first->second;
				}
				
				return nullptr;
			}
			
			void remove(unsigned int id)
			{
				if(components.find(id) != components.end())
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
			//util::AssocMap<unsigned int, C> components;
			google::dense_hash_map<int, C> components;
			
		private:
			virtual void addImpl(const C&)
			{}
			
			virtual void removeImpl(unsigned int)
			{}
	};
}

#endif // SYSTEM_HPP
