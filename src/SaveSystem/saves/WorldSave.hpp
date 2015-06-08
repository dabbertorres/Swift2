#ifndef SWIFT_WORLD_SAVE_HPP
#define SWIFT_WORLD_SAVE_HPP

#include <map>

#include "World/World.hpp"

namespace swift
{
	class WorldSave
	{
		friend class SaveManager;
		friend class Save;
		friend class Allocator;
		
		public:
			// a map of maps of maps.
			// outer map: map of entities
			// middle maps: map of components
			// inner maps: contain variables and values of Components for ids
			using VariableMap = std::map<std::string, std::string>;
			using ComponentMap = std::map<unsigned int, VariableMap>;
			using Data = std::map<Component::Type, ComponentMap>;
			
			virtual ~WorldSave() = default;
			
			// loads data to the given World
			virtual void load(World& w);
			
			// saves data from the given World
			virtual void save(const World& w);
			
			const std::string& getName() const;
			const std::string& getTilemap() const;
			
		protected:
			WorldSave(const World& w);
			WorldSave(const std::string& n);
			
			Data components;
		
		private:
			std::string name;
			std::string tilemap;
			
		public:
			struct Allocator : std::allocator<WorldSave>
			{
				template<typename T, typename... Args>
				void construct(T* p, Args&&... args)
				{
					new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
				}

				template<typename T>
				struct rebind
				{
					using other = WorldSave::Allocator;
				};
				
				using value_type = WorldSave;
			};
	};
}

#endif // SWIFT_WORLD_SAVE_HPP
