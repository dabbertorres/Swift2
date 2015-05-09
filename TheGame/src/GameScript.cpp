#include "GameScript.hpp"

#include "../../src/Math/Math.hpp"

#include "../../src/ResourceManager/AssetManager.hpp"

namespace tg
{
	sf::RenderWindow* GameScript::window = nullptr;
	swift::AssetManager* GameScript::assets = nullptr;
	sf::Clock* GameScript::clock = nullptr;
	swift::Settings* GameScript::settings = nullptr;
	swift::KeyboardManager* GameScript::keyboard = nullptr;
	swift::World* GameScript::world = nullptr;
	GamePlay* GameScript::play = nullptr;
	swift::ScriptManager* GameScript::scripts = nullptr;

	GameScript::GameScript()
	{
		addVariables();
		addClasses();
		addFunctions();
	}

	void GameScript::addVariables()
	{

	}

	void GameScript::addClasses()
	{

	}

	void GameScript::addFunctions()
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
		luaState["getPlayer"] = &getPlayer;
		luaState["isAround"] = &isAround;
		luaState["getCurrentWorld"] = &getCurrentWorld;
		luaState["setCurrentWorld"] = &setCurrentWorld;

		// tilemap
		luaState["getTileSize"] = &getTileSize;

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

	void GameScript::setWindow(sf::RenderWindow& win)
	{
		window = &win;
	}

	void GameScript::setAssetManager(swift::AssetManager& am)
	{
		assets = &am;
	}

	void GameScript::setClock(sf::Clock& c)
	{
		clock = &c;
	}

	void GameScript::setSettings(swift::Settings& s)
	{
		settings = &s;
	}

	void GameScript::setKeyboard(swift::KeyboardManager& k)
	{
		keyboard = &k;
	}

	void GameScript::setWorld(swift::World& w)
	{
		world = &w;
	}

	void GameScript::setWorld(std::nullptr_t)
	{
		world = nullptr;
	}

	void GameScript::setPlayState(GamePlay& p)
	{
		play = &p;
	}

	void GameScript::setScriptManager(swift::ScriptManager& sm)
	{
		scripts = &sm;
	}

	const swift::World* GameScript::getWorld()
	{
		return world;
	}

	/* Lua converted functions */
	// Utility
	std::tuple<unsigned, unsigned> GameScript::getWindowSize()
	{
		if(window)
		{
			return std::make_tuple(window->getSize().x, window->getSize().y);
		}
		else
		{
			return std::make_tuple(0u, 0u);
		}
	}

	float GameScript::getTime()
	{
		if(clock)
		{
			return clock->getElapsedTime().asSeconds();
		}
		else
		{
			return 0.f;
		}
	}

	void GameScript::doKeypress(std::string k)
	{
		if(keyboard)
		{
			keyboard->call(k);
		}
	}

	void GameScript::logMsg(std::string m)
	{
		swift::log << m << '\n';
	}

	// Play
	bool GameScript::addScript(std::string s)
	{
		if(scripts)
		{
			return scripts->add(s);
		}
		else
		{
			return false;
		}
	}

	bool GameScript::removeScript(std::string s)
	{
		if(scripts)
		{
			return scripts->remove(s);
		}
		else
		{
			return false;
		}
	}

	// World
	unsigned int GameScript::newEntity()
	{
		if(world)
		{
			return world->createEntity();
		}
		else
		{
			return 0;
		}
	}

	bool GameScript::removeEntity(int e)
	{
		if(world)
		{
			return world->destroyEntity(e);
		}
		else
		{
			return false;
		}
	}

	std::vector<unsigned int> GameScript::getEntities()
	{
		if(world)
		{
			return world->getEntities();
		}
		else
			return std::vector<unsigned int> {};
	}

	unsigned int GameScript::getPlayer()
	{
		if(play)
		{
			return play->getPlayer();
		}
		else
		{
			return 0;
		}
	}

	bool GameScript::isAround(swift::Physical* p, float x, float y, float r)
	{
		if(p)
			return swift::math::distance(p->position, {x, y}) <= r;
		else
		{
			return false;
		}
	}

	std::string GameScript::getCurrentWorld()
	{
		if(world)
		{
			std::string name = world->getName();
			return name;
		}
		else
		{
			return "nil";
		}
	}

	bool GameScript::setCurrentWorld(std::string s, std::string mf)
	{
		if(play)
		{
			play->changeWorld(s, mf);
			return true;
		}
		else
		{
			return false;
		}
	}

	// tilemap
	std::tuple<int, int> GameScript::getTileSize()
	{
		if(world)
		{
			sf::Vector2u ts = world->tilemap.getTileSize();
			return std::make_tuple(ts.x, ts.y);
		}
		else
		{
			return std::make_tuple(0, 0);
		}
	}

	// Entity System
	bool GameScript::add(unsigned int id, std::string c)
	{
		if(id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool GameScript::remove(unsigned int id, std::string c)
	{
		if(id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool GameScript::has(unsigned int id, std::string c)
	{
		if(id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Drawable
	swift::Drawable* GameScript::getDrawable(unsigned int id)
	{
		if(id)
		{
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}

	bool GameScript::setTexture(swift::Drawable* d, std::string t)
	{
		if(d)
		{
			d->sprite.setTexture(*assets->getTexture(t));
			d->texture = t;
			return true;
		}
		else
		{
			return false;
		}
	}

	void GameScript::setTextureRect(swift::Drawable* d, int x, int y, int w, int h)
	{
		if(d)
			d->sprite.setTextureRect( {x, y, w, h});
	}

	std::tuple<float, float> GameScript::getSpriteSize(swift::Drawable* d)
	{
		if(d)
		{
			return std::make_tuple(d->sprite.getGlobalBounds().width, d->sprite.getGlobalBounds().height);
		}
		else
		{
			return std::make_tuple(0.f, 0.f);
		}
	}

	void GameScript::setScale(swift::Drawable* d, float x, float y)
	{
		if(d)
			d->sprite.setScale( {x, y});
	}

	// Movable
	swift::Movable* GameScript::getMovable(unsigned int id)
	{
		if(id)
		{
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}

	void GameScript::setMoveVelocity(swift::Movable* m, float v)
	{
		if(m)
		{
			m->moveVelocity = v;
		}
	}

	std::tuple<float, float> GameScript::getVelocity(swift::Movable* m)
	{
		if(m)
		{
			return std::make_tuple(m->velocity.x, m->velocity.y);
		}
		else
		{
			return std::make_tuple(0.f, 0.f);
		}
	}

	// Physical
	swift::Physical* GameScript::getPhysical(unsigned int id)
	{
		if(id)
		{
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}

	void GameScript::setPosition(swift::Physical* p, float x, float y)
	{
		if(p)
			p->position = {x, y};
	}

	std::tuple<float, float> GameScript::getPosition(swift::Physical* p)
	{
		if(p)
		{
			return std::make_tuple(p->position.x, p->position.y);
		}
		else
		{
			return std::make_tuple(0.f, 0.f);
		}
	}

	void GameScript::setSize(swift::Physical* p, unsigned x, unsigned y)
	{
		if(p)
			p->size = {x, y};
	}

	std::tuple<unsigned, unsigned> GameScript::getSize(swift::Physical* p)
	{
		if(p)
		{
			return std::make_tuple(p->size.x, p->size.y);
		}
		else
		{
			return std::make_tuple(0u, 0u);
		}
	}

	// Name
	swift::Name* GameScript::getName(unsigned int id)
	{
		if(id)
		{
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}

	void GameScript::setName(swift::Name* n, std::string name)
	{
		if(n)
		{
			n->name = name;
		}
	}

	std::string GameScript::getNameVal(swift::Name* n)
	{
		if(n)
		{
			return n->name;
		}
		else
		{
			return "null";
		}
	}

	// Noisy
	swift::Noisy* GameScript::getNoisy(unsigned int id)
	{
		if(id)
		{
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}

	void GameScript::setSound(swift::Noisy* n, std::string s)
	{
		if(n)
		{
			n->soundFile = s;
		}
	}

	std::string GameScript::getSound(swift::Noisy* n)
	{
		if(n)
		{
			return n->soundFile;
		}
		else
		{
			return "null";
		}
	}

	// Settings
	std::tuple<bool, std::string> GameScript::getSettingStr(std::string s)
	{
		std::string v;
		return std::make_tuple(settings->get(s, v), v);
	}

	std::tuple<bool, bool> GameScript::getSettingBool(std::string s)
	{
		bool v;
		return std::make_tuple(settings->get(s, v), v);
	}

	std::tuple<bool, float> GameScript::getSettingNum(std::string s)
	{
		float v;
		return std::make_tuple(settings->get(s, v), v);
	}
}
