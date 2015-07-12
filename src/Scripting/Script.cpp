#include "Script.hpp"

/* Assets */
#include "../ResourceManager/AssetManager.hpp"

#include "../World/World.hpp"

#include "../Math/Math.hpp"

#include <tinyxml2.h>

namespace swift
{
	std::string Script::resPath = "";

	Script::Script()
	:	file(""),
		done(false)
	{
		// We don't want to give the scripts access to os commands or file writing abilities
		// so we open all libraries but "io", "os", "package", and "debug"
		luaState.openLib("base", luaopen_base);
		luaState.openLib("coroutine", luaopen_coroutine);
		luaState.openLib("string", luaopen_string);
		luaState.openLib("table", luaopen_table);
		luaState.openLib("math", luaopen_math);
		luaState.openLib("bit32", luaopen_bit32);
		
		luaState["getResourcePath"] = &getResourcePath;
		
		// components table
		luaState["Components"]["Animated"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Animated);
		luaState["Components"]["BatchDrawable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::BatchDrawable);
		luaState["Components"]["Controllable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Controllable);
		luaState["Components"]["Drawable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Drawable);
		luaState["Components"]["Movable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Movable);
		luaState["Components"]["Name"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Name);
		luaState["Components"]["Noisy"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Noisy);
		luaState["Components"]["Pathfinder"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Pathfinder);
		luaState["Components"]["Physical"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Animated);
		luaState["Components"]["Scriptable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Animated);
	}
	
	Script::Script(const Script& other)
	:	file(other.getFile()),
		done(other.isDone())
	{
		// We don't want to give the scripts access to os commands or file writing abilities
		// so we open all libraries but "io", "os", "package", and "debug"
		luaState.openLib("base", luaopen_base);
		luaState.openLib("coroutine", luaopen_coroutine);
		luaState.openLib("string", luaopen_string);
		luaState.openLib("table", luaopen_table);
		luaState.openLib("math", luaopen_math);
		luaState.openLib("bit32", luaopen_bit32);
		
		luaState["getResourcePath"] = &getResourcePath;
		
		// components table
		luaState["Components"]["Animated"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Animated);
		luaState["Components"]["BatchDrawable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::BatchDrawable);
		luaState["Components"]["Controllable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Controllable);
		luaState["Components"]["Drawable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Drawable);
		luaState["Components"]["Movable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Movable);
		luaState["Components"]["Name"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Name);
		luaState["Components"]["Noisy"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Noisy);
		luaState["Components"]["Pathfinder"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Pathfinder);
		luaState["Components"]["Physical"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Animated);
		luaState["Components"]["Scriptable"] = static_cast<std::underlying_type<Component::Type>::type>(Component::Type::Animated);
	}

	bool Script::loadFromFile(const std::string& lfile)
	{
		// load engine variables to Lua
		addVariables();
		addClasses();
		addFunctions();
		
		bool loadResult = luaState.loadFile(lfile) == LUA_OK;

		if(!loadResult)
		{
			Logger::get() << "[ERROR]: Script: " << lfile << " - load: " << luaState.getErrors() << '\n';
		}

		bool runResult = luaState.run() == LUA_OK;

		if(!runResult)
		{
			Logger::get() << "[ERROR]: Script: " << lfile << " - run: " << luaState.getErrors() << '\n';
		}

		file = lfile;

		return loadResult && runResult;
	}

	void Script::start()
	{
		if(!luaState["Start"])
		{
			return;
		}

		luaState["Start"]();

		if(!luaState["Done"])
		{
			return;
		}

		done = luaState["Done"];
	}

	void Script::update()
	{
		if(!luaState["Update"])
		{
			return;
		}

		luaState["Update"]();

		if(!luaState["Done"])
		{
			return;
		}

		done = luaState["Done"];
	}

	bool Script::isDone() const
	{
		return done;
	}

	void Script::reset()
	{
		luaState.reload();

		// We don't want to give the scripts access to os commands or file writing abilities
		// so we open all libraries but "io", "os", "package", and "debug"
		luaState.openLib("base", luaopen_base);
		luaState.openLib("coroutine", luaopen_coroutine);
		luaState.openLib("string", luaopen_string);
		luaState.openLib("table", luaopen_table);
		luaState.openLib("math", luaopen_math);
		luaState.openLib("bit32", luaopen_bit32);

		addVariables();
		addClasses();
		addFunctions();

		loadFromFile(file);
	}

	void Script::setResourcePath(const std::string& rp)
	{
		resPath = rp;
	}
	
	const std::string& Script::getFile() const
	{
		return file;
	}
	
	std::string Script::getResourcePath()
	{
		return resPath;
	}
}
