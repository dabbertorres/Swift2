#include "Script.hpp"

/* Assets */
#include "../ResourceManager/AssetManager.hpp"

#include "../StateSystem/States/Play.hpp"

#include "../World/World.hpp"

#include <tinyxml2.h>

namespace swift
{
	sf::RenderWindow* Script::window = nullptr;
	AssetManager* Script::assets = nullptr;
	sf::Clock* Script::clock = nullptr;
	Settings* Script::settings = nullptr;
	KeyboardManager* Script::keyboard = nullptr;
	World* Script::world = nullptr;
	Play* Script::play = nullptr;

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

		addVariables();
		addClasses();
		addFunctions();
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
		luaState["Start"]();

		if(static_cast<bool>(luaState["Done"]) == true)
		{
			deleteMe = true;
		}
	}

	void Script::update()
	{
		luaState["Update"]();

		if(static_cast<bool>(luaState["Done"]) == true)
		{
			deleteMe = true;
		}
	}

	bool Script::load(const std::string& file)
	{
		tinyxml2::XMLDocument loadFile;
		tinyxml2::XMLError result = loadFile.LoadFile(file.c_str());

		if(result != tinyxml2::XML_SUCCESS)
		{
			log << "Loading script save file \"" << file << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* root = loadFile.FirstChildElement("script");
		if(root == nullptr)
		{
			log << "Script save file \"" << file << "\" does not have a \"script\" root element.\n";
			return false;
		}

		tinyxml2::XMLElement* variable = root->FirstChildElement("variable");
		while(variable != nullptr)
		{
			std::string name = variable->Attribute("name");

			// boolean
			if(name[0] == 'b')
			{
				bool value;
				variable->QueryBoolText(&value);
				luaState[name.substr(1).c_str()] = value;
			}
			// number
			else if(name[0] == 'n')
			{
				float value;
				variable->QueryFloatText(&value);
				luaState[name.substr(1).c_str()] = value;
			}
			else
			{
				std::string text = variable->GetText();
				luaState[name.c_str()] = text;
			}

			variable = variable->NextSiblingElement("variable");
		}

		return true;
	}

	bool Script::save(const std::string& file)
	{
		// get all variables to save
		std::vector<std::string> variablesToSave = luaState["Save"];

		// save all variables to save file
		tinyxml2::XMLDocument saveFile;
		tinyxml2::XMLError result = saveFile.LoadFile(file.c_str());

		if(result != tinyxml2::XML_SUCCESS)
		{
			log << "Loading script save file \"" << file << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* root = saveFile.FirstChildElement("script");
		if(root == nullptr)
		{
			log << "Script save file \"" << file << "\" does not have a \"script\" root element.\n";
			return false;
		}

		root->DeleteChildren();

		for(auto& v : variablesToSave)
		{
			tinyxml2::XMLElement* newVariable = saveFile.NewElement("variable");
			newVariable->SetAttribute("name", v.c_str());

			// boolean
			if(v[0] == 'b')
			{
				bool value = luaState[v.substr(1).c_str()];
				newVariable->SetText(value);
			}
			// number
			else if(v[0] == 'n')
			{
				float value = luaState[v.substr(1).c_str()];
				newVariable->SetText(value);
			}
			else
			{
				std::string value = luaState[v.c_str()];
				newVariable->SetText(value.c_str());
			}

			root->InsertEndChild(newVariable);
		}

		saveFile.SaveFile(file.c_str());

		return true;
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

	void Script::setKeyboard(KeyboardManager& k)
	{
		keyboard = &k;
	}

	void Script::setWorld(World& w)
	{
		world = &w;
	}

	void Script::setWorld(std::nullptr_t)
	{
		world = nullptr;
	}
	
	void Script::setPlayState(Play& p)
	{
		play = &p;
	}

	const World* Script::getWorld()
	{
		return world;
	}

	void Script::addVariables()
	{
	}

	void Script::addClasses()
	{
	}

	void Script::addFunctions()
	{
		// utility functions
		luaState["getWindowSize"] = &getWindowSize;
		luaState["getTime"] = &getTime;
		luaState["doKeypress"] = &doKeypress;
		luaState["log"] = &logMsg;
		
		// play
		luaState["addScript"] = &addScript;
		luaState["removeScript"] = &removeScript;
		
		// world
		luaState["newEntity"] = &newEntity;
		luaState["removeEntity"] = &removeEntity;
		luaState["getEntities"] = &getEntities;
		luaState["getEntity"] = &getEntity;
		luaState["getPlayer"] = &getPlayer;
		luaState["isAround"] = &isAround;
		luaState["getWorldSize"] = &getWorldSize;
		luaState["getCurrentWorld"] = &getCurrentWorld;
		
		// Entity System
		luaState["add"] = &add;
		luaState["remove"] = &remove;
		luaState["has"] = &has;
		
		// Drawable
		luaState["getDrawable"] = &getDrawable;
		luaState["setTexture"] = &setTexture;
		luaState["setTextureRect"] = &setTextureRect;
		luaState["getSpriteSize"] = &getSpriteSize;
		luaState["setScale"] = &setScale;
		
		// Movable
		luaState["getMovable"] = &getMovable;
		luaState["setMoveVelocity"] = &setMoveVelocity;
		luaState["getVelocity"] = &getVelocity;
		
		// Physical
		luaState["getPhysical"] = &getPhysical;
		luaState["setPosition"] = &setPosition;
		luaState["getPosition"] = &getPosition;
		luaState["setSize"] = &setSize;
		luaState["getSize"] = &getSize;
		
		// Name
		luaState["getName"] = &getName;
		luaState["setName"] = &setName;
		luaState["getNameVal"] = &getNameVal;
		
		// Noisy
		luaState["getNoisy"] = &getNoisy;
		luaState["setSound"] = &setSound;
		luaState["getSound"] = &getSound;
		
		// Settings
		luaState["getSettingStr"] = &getSettingStr;
		luaState["getSettingBool"] = &getSettingBool;
		luaState["getSettingNum"] = &getSettingNum;
	}
	
	/* Lua converted functions */
	// Utility
	std::tuple<unsigned, unsigned> Script::getWindowSize()
	{
		if(window)
			return std::make_tuple(window->getSize().x, window->getSize().y);
		else
			return std::make_tuple(0u, 0u);
	}
	
	float Script::getTime()
	{
		if(clock)
			return clock->getElapsedTime().asSeconds();
		else
			return 0.f;
	}
	
	void Script::doKeypress(std::string k)
	{
		if(keyboard)
			keyboard->call(k);
	}
	
	void Script::logMsg(std::string m)
	{
		log << m << '\n';
	}

	// Play
	bool Script::addScript(std::string s)
	{
		if(play)
			return play->addScript(s);
		else
			return false;
	}
	
	bool Script::removeScript(std::string s)
	{
		if(play)
			return play->removeScript(s);
		else
			return false;
	}
	
	// World
	Entity* Script::newEntity()
	{
		if(world)
			return world->addEntity();
		else
			return nullptr;
	}
	
	bool Script::removeEntity(int e)
	{
		if(world)
			return world->removeEntity(e);
		else
			return false;
	}
	
	std::vector<Entity*> Script::getEntities()
	{
		if(world)
			return world->getEntities();
		else
			return std::vector<Entity*>{};
	}
	
	Entity* Script::getEntity(int e)
	{
		if(world)
			return world->getEntity(e);
		else
			return nullptr;
	}
	
	Entity* Script::getPlayer()
	{
		if(world)
			return world->getEntity(0);
		else
			return nullptr;
	}
	
	bool Script::isAround(Physical* p, float x, float y, float r)
	{
		if(world)
			return world->distance(p->position, {x, y}) <= r;
		else
			return false;
	}
	
	std::tuple<int, int> Script::getWorldSize()
	{
		if(world)
			return std::make_tuple(world->getSize().x, world->getSize().y);
		else
			return std::make_tuple(0, 0);
	}
	
	std::string Script::getCurrentWorld()
	{
		if(world)
			return world->getName();
		else
			return "nil";
	}
		
	// Entity System
	bool Script::add(Entity* e, std::string c)
	{
		if(e)
			return e->add(c);
		else
			return false;
	}
	
	bool Script::remove(Entity* e, std::string c)
	{
		if(e)
			return e->remove(c);
		else
			return false;
	}
	
	bool Script::has(Entity* e, std::string c)
	{
		if(e)
			return e->has(c);
		else
			return false;
	}

	// Drawable
	Drawable* Script::getDrawable(Entity* e)
	{
		if(e && e->has<Drawable>())
			return e->get<Drawable>();
		else
			return nullptr;
	}
	
	bool Script::setTexture(Drawable* d, std::string t)
	{
		if(d)
		{
			d->sprite.setTexture(assets->getTexture(t));
			d->texture = t;
			return true;
		}
		else
			return false;
	}
	
	void Script::setTextureRect(Drawable* d, int x, int y, int w, int h)
	{
		if(d)
			d->sprite.setTextureRect({x, y, w, h});
	}
	
	std::tuple<float, float> Script::getSpriteSize(Drawable* d)
	{
		if(d)
			return std::make_tuple(d->sprite.getGlobalBounds().width, d->sprite.getGlobalBounds().height);
		else
			return std::make_tuple(0.f, 0.f);
	}
	
	void Script::setScale(Drawable* d, float x, float y)
	{
		if(d)
			d->sprite.setScale({x, y});
	}
	
	// Movable
	Movable* Script::getMovable(Entity* e)
	{
		if(e && e->has<Movable>())
			return e->get<Movable>();
		else
			return nullptr;
	}
	
	void Script::setMoveVelocity(Movable* m, float v)
	{
		if(m)
			m->moveVelocity = v;
	}
	
	std::tuple<float, float> Script::getVelocity(Movable* m)
	{
		if(m)
			return std::make_tuple(m->velocity.x, m->velocity.y);
		else
			return std::make_tuple(0.f, 0.f);
	}

	// Physical
	Physical* Script::getPhysical(Entity* e)
	{
		if(e && e->has<Physical>())
			return e->get<Physical>();
		else
			return nullptr;
	}
	
	void Script::setPosition(Physical* p, float x, float y)
	{
		if(p)
			p->position = {x, y};
	}
	
	std::tuple<float, float> Script::getPosition(Physical* p)
	{
		if(p)
			return std::make_tuple(p->position.x, p->position.y);
		else
			return std::make_tuple(0.f, 0.f);
	}
	
	void Script::setSize(Physical* p, unsigned x, unsigned y)
	{
		if(p)
			p->size = {x, y};
	}
	
	std::tuple<unsigned, unsigned> Script::getSize(Physical* p)
	{
		if(p)
			return std::make_tuple(p->size.x, p->size.y);
		else
			return std::make_tuple(0u, 0u);
	}

	// Name
	Name* Script::getName(Entity* e)
	{
		if(e && e->has<Name>())
			return e->get<Name>();
		else
			return nullptr;
	}
	
	void Script::setName(Name* n, std::string name)
	{
		if(n)
			n->name = name;
	}
	
	std::string Script::getNameVal(Name* n)
	{
		if(n)
			return n->name;
		else
			return "null";
	}

	// Noisy
	Noisy* Script::getNoisy(Entity* e)
	{
		if(e && e->has<Noisy>())
			return e->get<Noisy>();
		else
			return nullptr;
	}
	
	void Script::setSound(Noisy* n, std::string s)
	{
		if(n)
			n->soundFile = s;
	}
	
	std::string Script::getSound(Noisy* n)
	{
		if(n)
			return n->soundFile;
		else
			return "null";
	}
	
	// Settings
	std::tuple<bool, std::string> Script::getSettingStr(std::string s)
	{
		std::string v;
		return std::make_tuple(settings->get(s, v), v);
	}
	
	std::tuple<bool, bool> Script::getSettingBool(std::string s)
	{
		bool v;
		return std::make_tuple(settings->get(s, v), v);
	}
	
	std::tuple<bool, float> Script::getSettingNum(std::string s)
	{
		float v;
		return std::make_tuple(settings->get(s, v), v);
	}
}
