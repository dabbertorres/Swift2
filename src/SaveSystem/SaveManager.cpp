#include "SaveManager.hpp"

#include <stdexcept>
#include <fstream>
#include <dirent.h>

#ifdef __linux__
	#include <unistd.h>
	#include <sys/stat.h>
#elif _WIN32
	#include <windows.h>
#endif

#include "../Logger/Logger.hpp"
#include "Save.hpp"

namespace swift
{
	constexpr char SAVE_PATH[] = "saves/";
	std::string SaveManager::resPath = "";
	
	Save SaveManager::newSave(std::string dir, bool force)
	{
		if(resPath.empty())
			return Save("");
			
		// make it a dir if it isn't
		if(dir.back() != '/')
			dir += '/';
		
		if(doesSaveExist(dir))
		{
			if(force)
			{
				// delete old save
				deleteSave(dir);
			}
			else
			{
				return Save("");
			}
		}
		
		// prepend the full path
		dir = resPath + SAVE_PATH + dir;
		
#ifdef __linux__
		if(mkdir(dir.c_str(), 0700) != 0)
#elif _WIN32
		if(CreateDirectory(dir.c_str(), NULL))
#endif
		{
			// make lastWorld file in new save dir
			std::ofstream fout;
			
			fout.open(dir + "lastWorld");
			
			if(fout.good())
			{
				return Save(dir);
			}
			
			return Save("");
		}
		
		return Save("");
	}
	
	bool SaveManager::doesSaveExist(std::string s)
	{
		if(resPath.empty())
			return false;
		
		// make it a dir if it isn't
		if(s.back() != '/')
			s += '/';
		
		// prepend the full path
		s = resPath + SAVE_PATH + s;
		
#ifdef __linux__
		struct stat st;	// dummy required for stat function
		
		// does save dir exist?
		if(stat(s.c_str(), &st) == 0)
		{
			// does 'lastWorld' file in save dir exist?
			s += "lastWorld";
			return stat(s.c_str(), &st) == 0;
		}
#elif _WIN32
		auto ftyp = GetFileAttributes(s.c_str());
		
		// error out
		if(ftyp == INVALID_FILE_ATTRIBUTES)
			return false;
		
		// is it a dir?
		if(ftyp & FILE_ATTRIBUTE_DIRECTORY)
		{
			// check the file
			s += "lastWorld";
			ftyp = GetFileAttributes(s.c_str());
			
			// error out
			if(ftyp == INVALID_FILE_ATTRIBUTES)
				return false;
			
			// success?
			return ftyp & FILE_ATTRIBUTE_NORMAL;
		}
#endif

		return false;
	}
	
	bool SaveManager::save(const Save& save)
	{
		if(resPath.empty())
			return false;
		
		if(!writeLastWorld(save))
			return false;
	}
	
	Save SaveManager::load(const std::string& dir)
	{
		if(resPath.empty())
			return Save("");
		
		Save save(dir);
		
		if(!readLastWorld(save))
			return Save("");
	}
	
	void SaveManager::setResourcePath(const std::string& rp)
	{
		resPath = rp;
	}
	
	bool SaveManager::deleteSave(const std::string& dirStr)
	{
		DIR* dir = nullptr;
		struct dirent* entry = nullptr;

		dir = opendir(dirStr.c_str());

		if(dir == nullptr)
		{
			log << "Unable to delete save: " << dirStr << "\n";
			return false;
		}
		
		// delete everything in the dir
		while((entry = readdir(dir)))
		{
			// if the entry is a directory, but is not the current or parent directory
			if(entry->d_type == DT_DIR && !(std::string(entry->d_name).compare(".") == 0 || std::string(entry->d_name).compare("..") == 0))
			{
				deleteSave(dirStr + std::string(entry->d_name));	// recursive on child directory
			}
			// entry is a file
			else if(entry->d_type == DT_REG)
			{
#ifdef __linux__
				unlink(entry->d_name);
#elif _WIN32
				DeleteFile(entry->d_name);
#endif
			}
		}

		closedir(dir);
		
		// finally, delete the now empty dir
#ifdef __linux__
		rmdir(dirStr.c_str());
#elif _WIN32
		RemoveDirectory(entry->d_name);
#endif
		
		return true;
	}
	
	bool SaveManager::readLastWorld(Save& save)
	{
		std::ifstream fin;
		
		fin.open(resPath + SAVE_PATH + save.getName() + "/lastWorld");
		
		if(fin.bad())
			return false;
		
		std::string worldName = "";
		
		std::getline(fin, worldName);
		
		worldName = worldName.substr(worldName.find('=') + 1);
		
		save.setLastWorld(worldName);
		
		return true;
	}
	
	bool SaveManager::writeLastWorld(const Save& save)
	{	
		std::ofstream fout;
		
		fout.open(resPath + SAVE_PATH + save.getName() + "/lastWorld");
		
		if(fout.bad())
			return false;
		
		fout << "name=" << save.getLastWorld();
		
		return true;
	}
}
