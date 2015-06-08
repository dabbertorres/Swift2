#ifndef SWIFT_SAVE_MANAGER_HPP
#define SWIFT_SAVE_MANAGER_HPP

#include <string>

#include "FileSystem/gfs.hpp"

#include "Save.hpp"

namespace swift
{
	class SaveManager
	{
		public:
			static void setResourcePath(const gfs::Path& rp);
			
			static bool doesSaveExist(const std::string& save);
			
			static bool deleteSave(const std::string& saveDir);
			
			static bool save(const Save& save, bool force = false);
			static bool load(Save& save);
			
		private:
			SaveManager() = default;
			
			// reads given file's data into the given Save
			static bool loadWorld(const gfs::Path& path, WorldSave& save);
			static bool loadScript(const gfs::Path& path, ScriptSave& save);
			
			// writes given Save's data into the given file
			static bool saveWorld(const gfs::Path& path, const WorldSave& save);
			static bool saveScript(const gfs::Path& path, const ScriptSave& save);
			
			static bool readLastWorld(Save& save);
			static bool writeLastWorld(const Save& save);
			
			// prepend the full path
			static gfs::Path makePath(const std::string& path);
			
			static gfs::Path resPath;
	};
}

#endif // SWIFT_SAVE_MANAGER_HPP
