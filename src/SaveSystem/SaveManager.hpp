#ifndef SWIFT_SAVE_MANAGER_HPP
#define SWIFT_SAVE_MANAGER_HPP

#include <string>

namespace swift
{
	class Save;
	
	class SaveManager
	{
		public:
			static Save newSave(std::string dir, bool force = false);
			static bool doesSaveExist(std::string s);
			
			static bool save(const Save& save);
			static Save load(const std::string& dir);
			
			static void setResourcePath(const std::string& rp);

		private:
			static bool deleteSave(const std::string& dir);
			
			static bool readLastWorld(Save& save);
			static bool writeLastWorld(const Save& save);
			
			static std::string resPath;
	};
}

#endif // SWIFT_SAVE_MANAGER_HPP
