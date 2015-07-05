#ifndef SWIFT_SAVE_HPP
#define SWIFT_SAVE_HPP

#include <string>
#include <vector>

#include "saves/ScriptSave.hpp"
#include "saves/WorldSave.hpp"

namespace swift
{
	class Save
	{
		friend class SaveManager;
		
		public:
			using ScriptSaves = std::vector<ScriptSave, ScriptSave::Allocator>;
			using WorldSaves = std::vector<WorldSave, WorldSave::Allocator>;
			
			Save(const std::string& n);
			~Save() = default;
			
			bool isValid() const;
			
			const std::string& getName() const;
			const std::string& getLastWorld() const;
			const ScriptSaves& getScriptSaves() const;
			const WorldSaves& getWorldSaves() const;
			
			// called by user, not by SaveManager
			void setLastWorld(const std::string& worldName);
			void addScript(Script& script);
			void addWorld(const World& world);

		private:
			std::string name;
			std::string lastWorld;
			
			ScriptSaves scripts;
			WorldSaves worlds;
	};
}

#endif // SWIFT_SAVE_HPP
