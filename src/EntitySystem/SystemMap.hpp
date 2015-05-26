#ifndef SWIFT_SYSTEM_MAP_HPP
#define SWIFT_SYSTEM_MAP_HPP

#include "Component.hpp"
#include "System.hpp"

#include "../Utility/AssocMap.hpp"

#include "../EntitySystem/Systems/AnimatedSystem.hpp"
#include "../EntitySystem/Systems/BatchDrawSystem.hpp"
#include "../EntitySystem/Systems/ControllableSystem.hpp"
#include "../EntitySystem/Systems/DrawableSystem.hpp"
#include "../EntitySystem/Systems/MovableSystem.hpp"
#include "../EntitySystem/Systems/NameSystem.hpp"
#include "../EntitySystem/Systems/NoisySystem.hpp"
#include "../EntitySystem/Systems/PathfinderSystem.hpp"
#include "../EntitySystem/Systems/PhysicalSystem.hpp"

namespace swift
{
	class SystemMap
	{
		private:
			using Map = util::AssocMap<Component::Type, BaseSystem*>;
		
		public:
			template<typename T = Component, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
			System<T>* get()
			{
				if(systems.find(T::type()) != systems.key_end())
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
				if(systems.find(t) != systems.key_end())
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
			Map::data_iterator begin()
			{
				return systems.begin();
			}
			
			Map::data_const_iterator begin() const
			{
				return systems.begin();
			}
			
			Map::data_iterator end()
			{
				return systems.end();
			}
			
			Map::data_const_iterator end() const
			{
				return systems.end();
			}
			
		private:
			Map systems;
	};
}

#endif	// SWIFT_SYSTEM_MAP_HPP
