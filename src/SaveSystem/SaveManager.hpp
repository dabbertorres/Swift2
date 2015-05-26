#ifndef SWIFT_SAVE_MANAGER_HPP
#define SWIFT_SAVE_MANAGER_HPP

#include <string>

#include "Save.hpp"

namespace swift
{
	class SaveManager
	{
		public:
			static bool doesSaveExist(const std::string& saveDir);
			
			static Save newSave(const std::string& saveDir, bool force = false);
			static bool deleteSave(const std::string& saveDir);
			
			static bool save(const Save& save);
			static Save load(const std::string& saveDir);
			
			static void setResourcePath(const std::string& rp);

		private:
			SaveManager() = default;
			
			// reads given file's data into the given Save
			static bool loadWorldSave(const std::string& wf, Save& save);
			static bool loadScriptSave(const std::string& sf, Save& save);
			
			// writes given Save's data into the given file
			static bool saveWorldSave(const std::string& wf, const Save& save);
			static bool saveScriptSave(const std::string& sf, const Save& save);
			
			static bool readLastWorld(Save& save);
			static bool writeLastWorld(const Save& save);
			
			// make it a dir if it isn't
			// prepend the full path
			static std::string fixPath(const std::string& path);
			
			static std::string resPath;
	};
}

#endif // SWIFT_SAVE_MANAGER_HPP
