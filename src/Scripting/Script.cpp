#include "Script.hpp"

#include <fstream>
#include <cassert>

#include "../ResourceManager/AssetManager.hpp"

#include "../World/World.hpp"

/* GUI */
#include "../GUI/Window.hpp"

#include "../GUI/Containers/Column.hpp"
#include "../GUI/Containers/Row.hpp"

#include "../GUI/Widgets/Button.hpp"
#include "../GUI/Widgets/Label.hpp"
#include "../GUI/Widgets/Slider.hpp"
#include "../GUI/Widgets/Spacer.hpp"
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
				keyboard(nullptr),
				stateReturn(nullptr),
				world(nullptr)
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
	
	void Script::setClock(sf::Clock& c)
	{
		clock = &c;
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
	
	void Script::setWorld(World& w)
	{
		world = &w;
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
		// ECS
		luaState["Entity"].SetClass<Entity>("add", static_cast<bool (Entity::*)(std::string)>(&Entity::add),
											"remove", static_cast<bool (Entity::*)(std::string)>(&Entity::remove),
											"has", static_cast<bool (Entity::*)(std::string) const>(&Entity::has),
											"get", static_cast<Drawable* (Entity::*)(std::string)>(&Entity::get),
											"get", static_cast<Movable* (Entity::*)(std::string)>(&Entity::get),
											"get", static_cast<Physical* (Entity::*)(std::string)>(&Entity::get));
		
		// each Component type
		luaState["Drawable"].SetClass<Drawable>();
		luaState["Movable"].SetClass<Movable>();
		luaState["Physical"].SetClass<Physical>();
		
		// vectors
		luaState["Vector2f"].SetClass<sf::Vector2f>();
		luaState["Vector2i"].SetClass<sf::Vector2i>();
		luaState["Vector2u"].SetClass<sf::Vector2u>();
		
		// GUI
		/*luaState["Column"].SetClass<cstr::Column>();
		luaState["Row"].SetClass<cstr::Row>();
		
		luaState["Button"].SetClass<cstr::Button>();
		luaState["Label"].SetClass<cstr::Label>();
		luaState["Slider"].SetClass<cstr::Slider>();
		luaState["Spacer"].SetClass<cstr::Spacer>();
		luaState["TextBox"].SetClass<cstr::TextBox>();
		luaState["Toggle"].SetClass<cstr::Toggle>();*/
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
		
		luaState["newEntity"] = [&]() -> Entity*
		{
			if(world)
				return &world->addEntity();
			else
				return nullptr;
		};
		
		// gui functions
		
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