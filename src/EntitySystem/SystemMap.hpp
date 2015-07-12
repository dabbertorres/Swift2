#ifndef SWIFT_SYSTEM_MAP_HPP
#define SWIFT_SYSTEM_MAP_HPP

#include "Component.hpp"
#include "System.hpp"

#include <google/dense_hash_map>

namespace swift
{
	class SystemMap
	{
		private:
			using Map = google::dense_hash_map<Component::Type, BaseSystem*>;
		
		public:
			template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
			System<T>* get()
			{
				if(systems.find(T::type()) != systems.end())
				{
					return static_cast<System<T>*>(systems[T::type()]);
				}
				else
				{
					return nullptr;
				}
			}
			
			BaseSystem* get(Component::Type t)
			{
				if(systems.find(t) != systems.end())
				{
					return systems[t];
				}
				else
				{
					return nullptr;
				}
			}
			
			void add(Component::Type t, BaseSystem* sys)
			{
				systems[t] = sys;
			}
			
			// forward iterator requests to the AssocMap
			Map::iterator begin()
			{
				return systems.begin();
			}
			
			Map::const_iterator begin() const
			{
				return systems.begin();
			}
			
			Map::iterator end()
			{
				return systems.end();
			}
			
			Map::const_iterator end() const
			{
				return systems.end();
			}
			
		private:
			Map systems;
	};
}

#endif	// SWIFT_SYSTEM_MAP_HPP
