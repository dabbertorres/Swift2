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
			// adding a specialization for each System enables a sort of "compile-time" switch statement.
			template<typename T>
			T& get();
			
			BaseSystem* get(Component::Type t)
			{
				return systems[t];
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
	
	template<>
	inline AnimatedSystem& SystemMap::get<AnimatedSystem>()
	{
		return static_cast<AnimatedSystem&>(*systems[Component::Type::Animated]);
	}
	
	template<>
	inline BatchDrawSystem& SystemMap::get<BatchDrawSystem>()
	{
		return static_cast<BatchDrawSystem&>(*systems[Component::Type::BatchDrawable]);
	}
	
	template<>
	inline ControllableSystem& SystemMap::get<ControllableSystem>()
	{
		return static_cast<ControllableSystem&>(*systems[Component::Type::Controllable]);
	}
	
	template<>
	inline DrawableSystem& SystemMap::get<DrawableSystem>()
	{
		return static_cast<DrawableSystem&>(*systems[Component::Type::Drawable]);
	}
	
	template<>
	inline MovableSystem& SystemMap::get<MovableSystem>()
	{
		return static_cast<MovableSystem&>(*systems[Component::Type::Movable]);
	}
	
	template<>
	inline NameSystem& SystemMap::get<NameSystem>()
	{
		return static_cast<NameSystem&>(*systems[Component::Type::Name]);
	}
	
	template<>
	inline NoisySystem& SystemMap::get<NoisySystem>()
	{
		return static_cast<NoisySystem&>(*systems[Component::Type::Noisy]);
	}
	
	template<>
	inline PathfinderSystem& SystemMap::get<PathfinderSystem>()
	{
		return static_cast<PathfinderSystem&>(*systems[Component::Type::Pathfinder]);
	}
	
	template<>
	inline PhysicalSystem& SystemMap::get<PhysicalSystem>()
	{
		return static_cast<PhysicalSystem&>(*systems[Component::Type::Physical]);
	}
}

#endif	// SWIFT_SYSTEM_MAP_HPP
