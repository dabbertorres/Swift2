#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Component.hpp"

#include <google/dense_hash_map>

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
	
	template<typename C, typename = typename std::enable_if<std::is_base_of<Component, C>::value>::type*>
	class System : public BaseSystem
	{
		public:
			System();
			
			virtual ~System() = default;
			
			virtual void update(float dt) = 0;
			
			unsigned int size() const;
			
			bool has(unsigned int id) const;

			C& get(unsigned int id);
			
			std::vector<const Component*> getAll() const;
			
			C* add(unsigned int id);
			
			void remove(unsigned int id);
			
			void clear();
			
			Component::Type typeEnum() const;
			
			using type = C;

		protected:
			google::dense_hash_map<int, C> components;
			
		private:
			virtual void addImpl(const C&)
			{}
			
			virtual void removeImpl(unsigned int)
			{}
	};
	
	template<typename C, typename E>
	System<C, E>::System()
	{
		components.set_empty_key(-1);
		components.set_deleted_key(-2);
	}
	
	template<typename C, typename E>
	unsigned int System<C, E>::size() const
	{
		return components.size();
	}
	
	template<typename C, typename E>
	bool System<C, E>::has(unsigned int id) const
	{
		return components.find(id) != components.end();
	}
	
	template<typename C, typename E>
	C& System<C, E>::get(unsigned int id)
	{
		return components[id];
	}
	
	template<typename C, typename E>
	std::vector<const Component*> System<C, E>::getAll() const
	{
		std::vector<const Component*> comps;
		
		for(auto& c : components)
		{
			comps.push_back(&c.second);
		}
		
		return comps;
	}
	
	template<typename C, typename E>
	C* System<C, E>::add(unsigned int id)
	{
		auto res = components.insert(std::make_pair(id, C(id)));
		
		if(res.second)
		{
			addImpl(res.first->second);
			return &res.first->second;
		}
		
		return nullptr;
	}
	
	template<typename C, typename E>
	void System<C, E>::remove(unsigned int id)
	{
		if(components.find(id) != components.end())
		{
			removeImpl(id);
			components.erase(id);
		}
	}
	
	template<typename C, typename E>
	void System<C, E>::clear()
	{
		components.clear();
	}
	
	template<typename C, typename E>
	Component::Type System<C, E>::typeEnum() const
	{
		return C::type();
	}
}

#endif // SYSTEM_HPP
