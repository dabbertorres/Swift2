#include "Script.hpp"

/* Assets */
#include "../ResourceManager/AssetManager.hpp"

#include "../World/World.hpp"

#include "../Math/Math.hpp"

#include <tinyxml2.h>

namespace swift
{
	Script::Script()
	:	file(""),
		deleteMe(false)
	{
		// We don't want to give the scripts access to os commands or file writing abilities
		// so we only open the necessary libraries
		luaState.openLib("base", luaopen_base);
		luaState.openLib("math", luaopen_math);
		luaState.openLib("string", luaopen_string);
		luaState.openLib("table", luaopen_table);
	}

	Script::~Script()
	{
	}

	bool Script::loadFromFile(const std::string& file)
	{
		bool loadResult = luaState.loadFile(file) == LUA_OK;

		if(!loadResult)
			log << "[ERROR]: " << file << " load: " << luaState.getErrors() << '\n';

		bool runResult = luaState.run() == LUA_OK;

		if(!runResult)
			log << "[ERROR]: " << file << " run: " << luaState.getErrors() << '\n';

		this->file = file;

		return loadResult && runResult;
	}

	void Script::start()
	{
		if(!luaState["Start"])
			return;

		luaState["Start"]();

		if(!luaState["Done"])
			return;

		deleteMe = luaState["Done"];
	}

	void Script::update()
	{
		if(!luaState["Update"])
			return;

		luaState["Update"]();

		if(!luaState["Done"])
			return;

		deleteMe = luaState["Done"];
	}

	bool Script::load(const std::string& lfile)
	{
		tinyxml2::XMLDocument loadFile;
		tinyxml2::XMLError result = loadFile.LoadFile(lfile.c_str());

		if(result != tinyxml2::XML_SUCCESS)
		{
			if(result == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
				log << "[INFO]: Save file \"" << lfile << "\" not found.\n";
			else
				log << "[ERROR]: Loading script save file \"" << lfile << "\" failed.\n";
			
			return false;
		}

		tinyxml2::XMLElement* root = loadFile.FirstChildElement("script");
		if(root == nullptr)
		{
			log << "[ERROR]: Script save file \"" << lfile << "\" does not have a \"script\" root element.\n";
			return false;
		}

		int total = 0;
		tinyxml2::XMLElement* variable = root->FirstChildElement("variable");
		while(variable != nullptr)
		{
			char type = variable->Attribute("type")[0];
			std::string value = variable->GetText();

			switch(type)
			{
				case 'n':	// number
					luaState.push(std::stod(value));
					break;
				case 'b':	// bool
					luaState.push(value != "0");
					break;
				case 's':	// string
					luaState.push(value);
					break;
				case '0':	// nil
					luaState.push(nullptr);
					break;
				default:
					break;
			}

			total++;
			variable = variable->NextSiblingElement("variable");
		}
		
		if(luaState["Load"])
			luaState.call("Load", total);
		else
			log << "[WARNING]: No Load function in script \"" << file << "\"\n";

		return true;
	}

	bool Script::save(const std::string& sfile)
	{
		// save all variables to save file
		tinyxml2::XMLDocument saveFile;
		tinyxml2::XMLError result = saveFile.LoadFile(sfile.c_str());

		if(result != tinyxml2::XML_SUCCESS && result != tinyxml2::XML_ERROR_EMPTY_DOCUMENT && result != tinyxml2::XML_ERROR_FILE_NOT_FOUND)
		{
			log << "[ERROR]: Loading script save file \"" << sfile << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* root = saveFile.FirstChildElement("script");
		if(root == nullptr)
		{
			log << "[INFO]: Script save file \"" << sfile << "\" does not have a \"script\" root element.\n";
			root = saveFile.NewElement("script");
			saveFile.InsertEndChild(root);
		}
		else
			root->DeleteChildren();

		luaState.clean();

		if(luaState["Save"])
		{
			// call save function
			luaState["Save"]();

			int totalRets = luaState.getTop();

			for(int i = 1; i <= totalRets; i++)
			{
				tinyxml2::XMLElement* newVariable = saveFile.NewElement("variable");

				auto type = luaState[i].getType();

				switch(type)
				{
					case LUA_TNUMBER:
						newVariable->SetAttribute("type", "n");
						newVariable->SetText(static_cast<float>(luaState[i]));
						break;
					case LUA_TBOOLEAN:
						newVariable->SetAttribute("type", "b");
						newVariable->SetText(static_cast<bool>(luaState[i]));
						break;
					case LUA_TSTRING:
					{
						newVariable->SetAttribute("type", "s");
						std::string temp = luaState[i];
						newVariable->SetText(temp.c_str());
						break;
					}
					default:
						newVariable->SetAttribute("type", "0");
						newVariable->SetText("nil");
						break;
				}

				root->InsertEndChild(newVariable);
			}

			if(saveFile.SaveFile(sfile.c_str()) != tinyxml2::XML_SUCCESS)
			{
				log << "[ERROR]: Saving script save file: " << sfile << " failed at saving.\n";
				return false;
			}

			return true;
		}
		
		log << "[INFO]: Script: " << file << " does not have a Save function.\n";
		
		return false;
	}

	bool Script::toDelete()
	{
		return deleteMe;
	}

	void Script::reset()
	{
		luaState.reload();

		// We don't want to give the scripts access to os commands or file writing abilities
		// so we only open the necessary libraries
		luaState.openLib("base", luaopen_base);
		luaState.openLib("math", luaopen_math);
		luaState.openLib("string", luaopen_string);
		luaState.openLib("table", luaopen_table);

		addVariables();
		addClasses();
		addFunctions();

		loadFromFile(file);
	}
}
