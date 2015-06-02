#include "SaveManager.hpp"

#include <stdexcept>
#include <fstream>
#include <dirent.h>

#ifdef __linux__
	#include <unistd.h>
	#include <sys/stat.h>
#elif _WIN32
	#include <windows.h>
#else
	#error "Unsupported operating system!"
#endif

#include "../Logger/Logger.hpp"

namespace swift
{
	constexpr char SAVE_PATH[] = "saves/";
	std::string SaveManager::resPath = "";
	
	bool SaveManager::doesSaveExist(const std::string& saveDir)
	{
		if(resPath.empty())
		{
			return false;
		}
		
		// make it a dir if it isn't
		// prepend the full path
		std::string path = fixPath(saveDir);
		
#ifdef __linux__
		struct stat st;	// dummy required for stat function
		
		// does save dir exist?
		if(stat(path.c_str(), &st) == 0)
		{
			// does 'lastWorld' file in save dir exist?
			path += "lastWorld";
			return stat(path.c_str(), &st) == 0;
		}
#elif _WIN32
		auto ftyp = GetFileAttributes(path.c_str());
		
		// error out
		if(ftyp == INVALID_FILE_ATTRIBUTES)
		{
			return false;
		}
		
		// is it a dir?
		if(ftyp & FILE_ATTRIBUTE_DIRECTORY)
		{
			// check the file
			path += "lastWorld";
			ftyp = GetFileAttributes(path.c_str());
			
			// error out
			if(ftyp == INVALID_FILE_ATTRIBUTES)
			{
				return false;
			}
			
			// success?
			return ftyp & FILE_ATTRIBUTE_NORMAL;
		}
#endif

		return false;
	}
	
	Save SaveManager::newSave(const std::string& saveDir, bool force)
	{
		if(resPath.empty())
		{
			return Save("");
		}
		
		if(doesSaveExist(saveDir))
		{
			if(force)
			{
				// delete old save
				deleteSave(saveDir);
			}
			else
			{
				return Save("");
			}
		}
		
		// make it a dir if it isn't
		std::string path = fixPath(saveDir);
		
#ifdef __linux__
		if(mkdir(path.c_str(), 0700) != 0)
#elif _WIN32
		if(CreateDirectory(path.c_str(), NULL))
#endif
		{
			// make lastWorld file in new save dir
			std::ofstream fout;
			
			fout.open(path + "lastWorld");
			
			if(fout.good())
			{
				return Save(saveDir);
			}
			
			return Save("");
		}
		
		return Save("");
	}
	
	bool SaveManager::deleteSave(const std::string& saveDir)
	{
		std::string path = fixPath(saveDir);
		
		DIR* dir = nullptr;
		struct dirent* entry = nullptr;

		dir = opendir(path.c_str());

		if(dir == nullptr)
		{
			Logger::get() << "Unable to delete save: " << saveDir << "\n";
			return false;
		}
		
		// delete everything in the dir
		while((entry = readdir(dir)))
		{
			// if the entry is a directory, but is not the current or parent directory
			if(entry->d_type == DT_DIR && !(std::string(entry->d_name).compare(".") == 0 || std::string(entry->d_name).compare("..") == 0))
			{
				deleteSave(path + std::string(entry->d_name));	// recursive on child directory
			}
			// entry is a file
			else if(entry->d_type == DT_REG)
			{
				std::string fullPath = path + entry->d_name;
#ifdef __linux__
				unlink(fullPath.c_str());
#elif _WIN32
				DeleteFile(fullPath.c_str());
#endif
			}
		}

		closedir(dir);
		
		// finally, delete the now empty dir
#ifdef __linux__
		rmdir(path.c_str());
#elif _WIN32
		RemoveDirectory(path.c_str());
#endif
		
		return true;
	}
	
	bool SaveManager::save(const Save& save)
	{
		if(resPath.empty() || !writeLastWorld(save))
		{
			return false;
		}
		
		// save worlds
		
		
		return true;
	}
	
	Save SaveManager::load(const std::string& saveDir)
	{
		if(resPath.empty())
		{
			return Save("");
		}
		
		Save save(saveDir);
		
		if(!readLastWorld(save))
		{
			return Save("");
		}
		
		// load last world
		// maybe load all world save files?
		
		
		return save;
	}
	
	void SaveManager::setResourcePath(const std::string& rp)
	{
		resPath = rp;
	}
	
	bool SaveManager::loadWorldSave(const std::string& wf, Save& save)
	{
		return true;
	}
	
	bool SaveManager::loadScriptSave(const std::string& sf, Save& save)
	{
		return true;
	}
	
	bool SaveManager::saveWorldSave(const std::string& wf, const Save& save)
	{
		return true;
	}
	
	bool SaveManager::saveScriptSave(const std::string& sf, const Save& save)
	{
		return true;
	}
	
	bool SaveManager::readLastWorld(Save& save)
	{
		std::ifstream fin;
		
		std::string path = fixPath(save.getName());
		
		fin.open(path + "lastWorld");
		
		if(fin.bad())
		{
			return false;
		}
		
		std::string worldName = "";
		
		std::getline(fin, worldName);
		
		worldName = worldName.substr(worldName.find('=') + 1);
		
		save.setLastWorld(worldName);
		
		return true;
	}
	
	bool SaveManager::writeLastWorld(const Save& save)
	{	
		std::ofstream fout;
		
		std::string path = fixPath(save.getName());
		
		fout.open(path + "lastWorld");
		
		if(fout.bad())
		{
			return false;
		}
		
		fout << "name=" << save.getLastWorld();
		
		return true;
	}
	
	std::string SaveManager::fixPath(const std::string& path)
	{
		if(path.back() != '/')
		{
			return resPath + SAVE_PATH + path + '/';
		}
		else
		{
			return resPath + SAVE_PATH + path;
		}
	}
}
