#include "Script.hpp"

#include <fstream>
#include <cassert>

#include "../ResourceManager/AssetManager.hpp"

/* GUI */
#include "../GUI/Window.hpp"
#include "../GUI/Widgets/Button.hpp"
#include "../GUI/Widgets/Label.hpp"
#include "../GUI/Widgets/TextBox.hpp"
#include "../GUI/Widgets/Toggle.hpp"

/* EntitySystem */
#include "../EntitySystem/Entity.hpp"

namespace swift
{
	sf::RenderWindow* Script::window = nullptr;
	AssetManager* Script::assets = nullptr;
	sf::Clock* Script::clock = nullptr;
	Settings* Script::settings = nullptr;
	
	Script::Script()
			:	gui(nullptr),
				stateReturn(nullptr)
	{
		deleteMe = false;
		
		// We don't want to give the scripts access to os commands or file writing abilities
		luaState.OpenLib("base", luaopen_base);
		luaState.OpenLib("math", luaopen_math);
		luaState.OpenLib("string", luaopen_string);
		luaState.OpenLib("table", luaopen_table);
		
		addVariables();
		addClasses();
		addFunctions();
	}

	Script::~Script()
	{
	}

	bool Script::loadFromFile(const std::string& file)
	{
		bool r = luaState.Load(file);	// r will be false if errors, true otherwise
		
		return r;
	}
	
	void Script::start()
	{
		luaState["Start"]();
		
		if(static_cast<bool>(luaState["Done"]) == true)
		{
			deleteMe = true;
		}
	}

	void Script::run()
	{
		luaState["Update"]();
		
		if(static_cast<bool>(luaState["Done"]) == true)
		{
			deleteMe = true;
		}
	}

	bool Script::toDelete()
	{
		return deleteMe;
	}
	
	void Script::setWindow(sf::RenderWindow& win)
	{
		window = &win;
	}
	
	void Script::setAssetManager(AssetManager& am)
	{
		assets = &am;
	}
	
	void Script::setSettings(Settings& s)
	{
		settings = &s;
	}
	
	void Script::setGUI(cstr::Window& ui)
	{
		gui = &ui;
	}
	
	void Script::setKeyboard(KeyboardManager& k)
	{
		keyboard = &k;
	}
	
	void Script::setStateReturn(State::Type& t)
	{
		stateReturn = &t;
	}
	
	void Script::setClock(sf::Clock& c)
	{
		clock = &c;
	}
	
	void Script::addVariables()
	{
		luaState["states"]["MainMenu"] = 0;
		luaState["states"]["Settings"] = 1;
		luaState["states"]["Play"] = 2;
		luaState["states"]["Exit"] = 3;
	}
	
	void Script::addClasses()
	{
		luaState["Entity"].SetClass<Entity>();
	}
	
	void Script::addFunctions()
	{
		// utility functions
		luaState["getWindowSize"] = [&]()
		{
			if(window)
				return std::make_tuple(window->getSize().x, window->getSize().y);
			else
				return std::make_tuple(0u, 0u);
		};
		
		luaState["getTime"] = [&]()
		{
			if(clock)
				return clock->getElapsedTime().asSeconds();
			else
				return 0.f;
		};
		
		luaState["doKeypress"] = [&](std::string k)
		{
			if(keyboard)
				keyboard->call(k);
		};
		
		// EntitySystem functions
		
		
		// gui functions
		luaState["setFont"] = [&](std::string f)
		{
			if(gui)
				gui->setFont(assets->getFont(f));
		};
		
		// State functions
		luaState["setStateReturn"] = [&](unsigned s)
		{
			*stateReturn = static_cast<State::Type>(s);
		};
		
		// Settings functions
		luaState["getSettingStr"] = [&](std::string n)
		{
			std::string v;
			return std::make_tuple(settings->get(n, v), v);
		};
		
		luaState["setSettingStr"] = [&](std::string n, std::string v)
		{
			return settings->set(n, v);
		};
		
		luaState["getSettingBool"] = [&](std::string n)
		{
			bool v;
			return std::make_tuple(settings->get(n, v), v);
		};
		
		luaState["setSettingBool"] = [&](std::string n, bool v)
		{
			return settings->set(n, v);
		};
		
		luaState["getSettingNum"] = [&](std::string n)
		{
			int v;
			return std::make_tuple(settings->get(n, v), v);
		};
		
		luaState["setSettingNum"] = [&](std::string n, int v)
		{
			return settings->set(n, v);
		};
	}
}