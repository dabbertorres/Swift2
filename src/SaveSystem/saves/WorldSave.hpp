#ifndef SWIFT_WORLD_SAVE_HPP
#define SWIFT_WORLD_SAVE_HPP

#include <map>

#include "../../World/World.hpp"

namespace swift
{
	class WorldSave
	{
		friend class SaveManager;
		
		public:
			// a map of maps of maps.
			// outer map: map of Component types
			// middle map: all components of one type by id
			// inner maps: contain variables and values of Components
			using Data = std::map<Component::Type, std::map<unsigned int, std::map<std::string, std::string>>>;
			
			WorldSave(const World& w);
			virtual ~WorldSave() = default;
			
			// loads data to the given World
			virtual void load(World& w);
			
			// saves data from the given World
			void save(const World& w);
			
			const std::string& getName() const;
			const std::string& getTilemap() const;
			
		private:
			WorldSave(const std::string& n, const std::string& tm, const Data& wd);
			
			std::string name;
			std::string tilemap;
			
			Data components;
	};
}

#endif // SWIFT_WORLD_SAVE_HPP
