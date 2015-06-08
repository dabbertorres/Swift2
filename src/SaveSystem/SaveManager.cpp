#include "SaveManager.hpp"

#include <fstream>
#include <tinyxml2.h>

#include "Logger/Logger.hpp"

namespace swift
{
	constexpr char SAVE_PATH[] = "../saves/";
	gfs::Path SaveManager::resPath;
	
	void SaveManager::setResourcePath(const gfs::Path& rp)
	{
		resPath = rp;
	}
	
	bool SaveManager::doesSaveExist(const std::string& saveDir)
	{
		// is resPath set to a valid directory?
		if(!resPath || resPath.type() != gfs::Path::Type::Directory)
		{
			return false;
		}
		
		gfs::Path path = makePath(saveDir);
		
		if(path && path.type() == gfs::Path::Type::Directory)
		{
			gfs::Path lastWorld = path / "lastWorld";
			
			return lastWorld && lastWorld.type() == gfs::Path::Type::File;
		}
		
		return false;
	}
	
	bool SaveManager::deleteSave(const std::string& saveDir)
	{
		if(!resPath || resPath.type() != gfs::Path::Type::Directory || !doesSaveExist(saveDir))
		{
			return false;
		}
		
		gfs::Path path = makePath(saveDir);
		
		if(path && path.type() == gfs::Path::Type::Directory)
		{
			gfs::PathContents contents = gfs::contents(path, true);
			
			for(auto& p : contents)
			{
				if(p.type() == gfs::Path::Type::Directory)
				{
					deleteSave(p);
				}
				else
				{
					gfs::erase(p);
				}
			}
			
			if(gfs::erase(path))
			{
				Logger::get() << "[INFO]: Deleted save: " << saveDir << '\n';
				
				return true;
			}
		}
		
		Logger::get() << "[WARNING]: Couldn't delete save: " << saveDir << '\n';
		
		return false;
	}
	
	bool SaveManager::save(const Save& save, bool force)
	{
		if(!resPath || resPath.type() != gfs::Path::Type::Directory)
		{
			return false;
		}
		
		if(!writeLastWorld(save))
		{
			return false;
		}
		
		if(doesSaveExist(save.getName()) && !force)
		{
			Logger::get() << "[WARNING]: Save: " << save.getName() << " already exists.\n";
			
			return false;
		}
		
		gfs::Path savePath = makePath(save.getName());
		
		// save worlds
		Save::WorldSaves worlds = save.getWorldSaves();
		
		for(auto& w : worlds)
		{
			gfs::Path worldPath = makePath(savePath / w.getName() + ".ws");
			if(!saveWorld(worldPath, w))
			{
				Logger::get() << "[ERROR]: Could not finish saving: " << save.getName() << " on world: " << w.getName() << '\n';
				return false;
			}
		}
		
		// save scripts
		Save::ScriptSaves scripts = save.getScriptSaves();
		
		for(auto& s : scripts)
		{
			gfs::Path scriptPath = makePath(savePath / s.getName() + ".ss");
			if(!saveScript(scriptPath, s))
			{
				Logger::get() << "[ERROR]: Could not finish saving: " << save.getName() << " on script: " << s.getName() << '\n';
				return false;
			}
		}
		
		Logger::get() << "[INFO]: Saved: " << save.getName() << '\n';
		
		return true;
	}
	
	bool SaveManager::load(Save& save)
	{
		if(!resPath || resPath.type() != gfs::Path::Type::Directory)
		{
			return false;
		}
		
		gfs::Path savePath = makePath(save.getName());
		
		if(!savePath || savePath.type() != gfs::Path::Type::Directory)
		{
			Logger::get() << "[ERROR]: Could not load: " << save.getName() << ". It does not exist as a directory.\n";
			return false;
		}
		
		if(!readLastWorld(save))
		{
			return false;
		}
		
		gfs::PathContents contents = gfs::contents(savePath);
		
		for(auto& p : contents)
		{
			// world
			if(p.ext() == "ws")
			{
				save.worlds.emplace_back(p.name());
				
				if(!loadWorld(p, save.worlds.back()))
				{
					Logger::get() << "[ERROR]: Could not load: " << save.getName() << " on world: " << p.name() << '\n';
					return false;
				}
			}
			// script
			else if(p.ext() == "ss")
			{
				save.scripts.emplace_back(p.name());
				
				if(!loadScript(p, save.scripts.back()))
				{
					Logger::get() << "[ERROR]: Could not load: " << save.getName() << " on script: " << p.name() << '\n';
					return false;
				}
			}
		}
		
		Logger::get() << "[INFO]: Finished loading: " << save.getName() << '\n';
		
		return true;
	}
	
	bool SaveManager::loadWorld(const gfs::Path& path, WorldSave& save)
	{
		std::string file = path;
		
		tinyxml2::XMLDocument loadFile;
		loadFile.LoadFile(file.c_str());

		if(loadFile.Error())
		{
			Logger::get() << "[ERROR]: Loading world save file \"" << path.name() << "\" failed.\n";
			Logger::get() << "\t: " << loadFile.GetErrorStr1() << '\n';
			Logger::get() << "\t: " << loadFile.GetErrorStr2() << '\n';
			return false;
		}

		auto* worldRoot = loadFile.FirstChildElement("World");

		if(worldRoot == nullptr)
		{
			Logger::get() << "[ERROR]: World save file \"" << path.name() << "\" does not have a \"World\" root element.\n";
			return false;
		}
		
		// get the World meta-info
		save.name = path.name();
		save.tilemap = worldRoot->Attribute("tilemap");
		
		save.components.clear();
		
		auto* componentType = worldRoot->FirstChildElement("Component");
		while(componentType != nullptr)
		{
			// get the type of Component we're dealing with
			std::string componentStr = componentType->Attribute("type");
			Component::Type typeVal = Component::type(componentStr.c_str());
			
			// create our map for this Component type
			save.components.emplace(typeVal, WorldSave::ComponentMap{});
			
			auto* componentInstance = componentType->FirstChildElement("id");
			while(componentInstance != nullptr)
			{
				// get the entity id of this Component instance
				unsigned int instanceID = componentInstance->UnsignedAttribute("val");
				
				// create our map of variables for this entity
				save.components[typeVal].emplace(instanceID, WorldSave::VariableMap{});
				
				auto* variableElement = componentInstance->FirstChildElement("variable");
				while(variableElement != nullptr)
				{
					save.components[typeVal][instanceID].emplace(variableElement->Attribute("name"), variableElement->GetText());
					
					variableElement = variableElement->NextSiblingElement("variable");
				}
				
				componentInstance = componentInstance->NextSiblingElement("id");
			}
			
			componentType = componentType->NextSiblingElement("Component");
		}
		
		return true;
	}
	
	bool SaveManager::loadScript(const gfs::Path& path, ScriptSave& save)
	{
		std::string file = path;
		
		tinyxml2::XMLDocument loadFile;
		loadFile.LoadFile(file.c_str());

		if(loadFile.Error())
		{
			Logger::get() << "[ERROR]: Loading script save file \"" << path.name() << "\" failed.\n";
			Logger::get() << "\t: " << loadFile.GetErrorStr1() << '\n';
			Logger::get() << "\t: " << loadFile.GetErrorStr2() << '\n';
			return false;
		}

		auto* scriptRoot = loadFile.FirstChildElement("World");

		if(scriptRoot == nullptr)
		{
			Logger::get() << "[ERROR]: Script save file \"" << path.name() << "\" does not have a \"Script\" root element.\n";
			return false;
		}
		
		save.variables.clear();
		
		auto* variable = scriptRoot->FirstChildElement("variable");
		while(variable != nullptr)
		{
			std::string varTypeStr = variable->Attribute("type");
			decltype(LUA_TNUMBER) varType = LUA_TNONE;
			
			if(varTypeStr == "nil")
			{
				varType = LUA_TNIL;
			}
			else if(varTypeStr == "bool")
			{
				varType = LUA_TBOOLEAN;
			}
			else if(varTypeStr == "num")
			{
				varType = LUA_TNUMBER;
			}
			else if(varTypeStr == "string")
			{
				varType = LUA_TSTRING;
			}
			
			save.variables.emplace_back(varType, variable->GetText());
			
			variable = variable->NextSiblingElement("variable");
		}
		
		return true;
	}
	
	bool SaveManager::saveWorld(const gfs::Path& path, const WorldSave& save)
	{
		tinyxml2::XMLDocument saveFile;
		
		auto* worldRoot = saveFile.NewElement("World");
		worldRoot->SetAttribute("tilemap", save.getTilemap().c_str());
		
		saveFile.InsertEndChild(worldRoot);
		
		for(auto& component : save.components)
		{
			auto* componentElement = saveFile.NewElement("Component");
			componentElement->SetAttribute("type", Component::type(component.first));
			
			worldRoot->InsertEndChild(componentElement);
			
			for(auto& id : component.second)
			{
				auto* idElement = saveFile.NewElement("id");
				idElement->SetAttribute("val", id.first);
				
				componentElement->InsertEndChild(idElement);
				
				for(auto& var : id.second)
				{
					auto* varElement = saveFile.NewElement("variable");
					varElement->SetAttribute("name", var.first.c_str());
					varElement->SetText(var.second.c_str());
					
					idElement->InsertEndChild(varElement);
				}
			}
		}
		
		std::string file = path;
		
		if(saveFile.SaveFile(file.c_str()) != tinyxml2::XMLError::XML_SUCCESS)
		{
			Logger::get() << "[ERROR]: Saving world save file \"" << path.name() << "\" failed.\n";
			Logger::get() << "\t: " << saveFile.GetErrorStr1() << '\n';
			Logger::get() << "\t: " << saveFile.GetErrorStr2() << '\n';
			return false;
		}
		
		return true;
	}
	
	bool SaveManager::saveScript(const gfs::Path& path, const ScriptSave& save)
	{
		tinyxml2::XMLDocument saveFile;
		
		auto* scriptRoot = saveFile.NewElement("Script");
		
		saveFile.InsertEndChild(scriptRoot);
		
		for(auto& var : save.variables)
		{
			std::string varTypeStr;
			
			switch(var.first)
			{
				case LUA_TNIL:
					varTypeStr = "nil";
					break;
				case LUA_TBOOLEAN:
					varTypeStr = "bool";
					break;
				case LUA_TNUMBER:
					varTypeStr = "num";
					break;
				case LUA_TSTRING:
					varTypeStr = "string";
					break;
				default:
					varTypeStr = "none";
					break;
			}
			
			auto* varElement = saveFile.NewElement("variable");
			varElement->SetAttribute("type", varTypeStr.c_str());
			varElement->SetText(var.second.c_str());
			
			scriptRoot->InsertEndChild(varElement);
		}
		
		return true;
	}
	
	bool SaveManager::readLastWorld(Save& save)
	{
		gfs::Path path = makePath(save.getName());
		
		if(!path || path.type() != gfs::Path::Type::Directory)
		{
			return false;
		}
		
		std::ifstream fin(path / "lastWorld");
		
		if(!fin)
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
		
		gfs::Path path = makePath(save.getName());
		
		fout.open(path / "lastWorld");
		
		if(!fout)
		{
			return false;
		}
		
		fout << "name=" << save.getLastWorld() << '\n';
		
		return true;
	}
	
	gfs::Path SaveManager::makePath(const std::string& path)
	{
		return resPath / SAVE_PATH / path;
	}
}
