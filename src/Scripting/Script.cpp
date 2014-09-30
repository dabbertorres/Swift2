#include "Script.hpp"

/* Assets */
#include "../ResourceManager/AssetManager.hpp"

/* Logger */
#include "../Logger/Logger.hpp"

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

#include "../World/World.hpp"

namespace swift
{
	sf::RenderWindow* Script::window = nullptr;
	AssetManager* Script::assets = nullptr;
	sf::Clock* Script::clock = nullptr;
	Settings* Script::settings = nullptr;
	Logger* Script::log = nullptr;
	
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
	
	void Script::setLogger(Logger& l)
	{
		log = &l;
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
		// vectors
		luaState["Vector2f"].SetClass<sf::Vector2f>("x", &sf::Vector2f::x, "y", &sf::Vector2f::y);
		luaState["Vector2i"].SetClass<sf::Vector2i>("x", &sf::Vector2i::x, "y", &sf::Vector2i::y);
		luaState["Vector2u"].SetClass<sf::Vector2u>("x", &sf::Vector2u::x, "y", &sf::Vector2u::y);
		
		// c++ containers
		luaState["entityList"].SetClass<std::vector<Entity*>>();
		
		// ECS
		luaState["Entity"].SetClass<Entity>("add", static_cast<bool (Entity::*)(std::string)>(&Entity::add),
											"remove", static_cast<bool (Entity::*)(std::string)>(&Entity::remove),
											"has", static_cast<bool (Entity::*)(std::string) const>(&Entity::has),
											"getDrawable", static_cast<Drawable* (Entity::*)()>(&Entity::get<Drawable>),
											"getMovable", static_cast<Movable* (Entity::*)()>(&Entity::get<Movable>),
											"getPhysical", static_cast<Physical* (Entity::*)()>(&Entity::get<Physical>),
											"getName", static_cast<Name* (Entity::*)()>(&Entity::get<Name>));
		
		// each Component type
		luaState["Drawable"].SetClass<Drawable>();
		luaState["Movable"].SetClass<Movable>();
		luaState["Physical"].SetClass<Physical>();
		luaState["Name"].SetClass<Name>();
		
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
		/* utility functions */
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
		
		luaState["log"] = [&](std::string m)
		{
			if(log)
				*log << m;
		};
		
		/* EntitySystem */
		// World
		luaState["newEntity"] = [&]() -> Entity*
		{
			if(world)
				return world->addEntity();
			else
				return nullptr;
		};
		
		luaState["getTotalEntities"] = [&]()
		{
			if(world)
				return static_cast<unsigned>(world->getEntities().size());
			else
				return 0u;
		};
		
		luaState["getEntity"] = [&](unsigned e) -> Entity*
		{
			if(world && e < world->getEntities().size())
				return world->getEntities()[e];
			else
				return nullptr;
		};
		
		luaState["calculateEntitiesAround"] = [&](float x, float y, float radius)
		{
			if(world)
				world->calculateEntitiesAround({x, y}, radius);
		};
		
		luaState["getTotalEntitiesAround"] = [&]()
		{
			if(world)
				return static_cast<unsigned>(world->getEntitiesAround().size());
			else
				return 0u;
		};
		
		luaState["getEntityAround"] = [&](unsigned e) -> Entity*
		{
			if(world && e < world->getEntitiesAround().size())
				return world->getEntities()[e];
			else
				return nullptr;
		};
		
		// Drawable
		luaState["setTexture"] = [&](Drawable* d, std::string t)
		{
			if(d)
			{
				d->sprite.setTexture(assets->getTexture(t));
				return true;
			}
			else
				return false;
		};
		
		luaState["setTextureRect"] = [&](Drawable* d, int x, int y, int w, int h)
		{
			if(d)
				d->sprite.setTextureRect({x, y, w, h});
		};
		
		luaState["getSpriteSize"] = [&](Drawable* d)
		{
			if(d)
				return std::make_tuple(d->sprite.getGlobalBounds().width, d->sprite.getGlobalBounds().height);
			else
				return std::make_tuple(0.f, 0.f);
		};
		
		luaState["setScale"] = [&](Drawable* d, float x, float y)
		{
			if(d)
				d->sprite.setScale(x, y);
		};
		
		// Movable
		luaState["setMoveVelocity"] = [&](Movable* m, float v)
		{
			if(m)
			{
				m->moveVelocity = v;
			}
		};
		
		luaState["getVelocity"] = [&](Movable* m)
		{
			if(m)
				return std::make_tuple(m->velocity.x, m->velocity.y);
			else
				return std::make_tuple(0.f, 0.f);
		};
		
		// Physical
		luaState["setPosition"] = [&](Physical* p, float x, float y)
		{
			if(p)
				p->position = {x, y};
			else if(p)
				p->position = {0, 0};
		};
		
		luaState["getPosition"] = [&](Physical* p)
		{
			if(p)
				return std::make_tuple(p->position.x, p->position.y);
			else
				return std::make_tuple(0.f, 0.f);
		};
		
		luaState["setSize"] = [&](Physical* p, unsigned x, unsigned y)
		{
			if(p)
				p->size = {x, y};
			else if(p)
				p->size = {0, 0};
		};
		
		luaState["getSize"] = [&](Physical* p)
		{
			if(p)
				return std::make_tuple(p->size.x, p->size.y);
			else
				return std::make_tuple(0u, 0u);
		};
		
		// Name
		luaState["setName"] = [&](Name* n, std::string s)
		{
			if(n)
				n->name = s;
		};
		
		luaState["getName"] = [&](Name* n) -> std::string
		{
			if(n)
				return n->name;
			else
				return "null";
		};
		
		/* gui functions */
		
		/* State */
		luaState["setStateReturn"] = [&](unsigned s)
		{
			*stateReturn = static_cast<State::Type>(s);
		};
		
		/* Settings */
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