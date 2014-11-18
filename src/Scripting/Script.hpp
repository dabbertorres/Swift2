#ifndef SCRIPT_HPP
#define SCRIPT_HPP

/*
 * Lua is expected to be compiled with float as lua_number!!!
 */

#include "LuaCpp/LuaCpp.hpp"

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../Settings/Settings.hpp"

#include "../KeyBindings/KeyboardManager.hpp"

#include "../Logger/Logger.hpp"

/* EntitySystem */
#include "../EntitySystem/Entity.hpp"

/*
 * Each Script object expects two functions to exist in the
 * Lua script:
 *
 * Start()
 * Update()
 *
 * 1 variable is expected to exist:
 * Done
 *
 * 'Done' should be set to false during 'Start'.
 *
 * Start is called during Script construction.
 * This function should only do setup, etc.
 *
 * Update is called every game tick. If the state of the script
 * should ever change, that code goes in here.
 *
 * Finish is called at a game tick that finds 'Done' to be true
 */

namespace swift
{
	class AssetManager;
	class World;
	class Play;
	
	class Script
	{
		public:
			Script();
			~Script();
			
			bool loadFromFile(const std::string& file);

			void start();

			void update();
			
			bool load(const std::string& file);
			bool save(const std::string& file);

			bool toDelete();
			
			// setters for variables that Lua has access to
			static void setWindow(sf::RenderWindow& win);
			static void setAssetManager(AssetManager& am);
			static void setClock(sf::Clock& c);
			static void setSettings(Settings& s);
			static void setKeyboard(KeyboardManager& k);
			static void setWorld(World& w);
			static void setWorld(std::nullptr_t);
			static void setPlayState(Play& p);
			
			// get world pointer for comparison
			static const World* getWorld();

		private:
			void addVariables();
			void addClasses();
			void addFunctions();
			
			lpp::State luaState;
			
			// Variables that need to be accessed by Lua
			static sf::RenderWindow* window;
			static AssetManager* assets;
			static sf::Clock* clock;
			static Settings* settings;
			static KeyboardManager* keyboard;
			static World* world;
			static Play* play;
			
			bool deleteMe;
			
			/* Lua converted functions */
			// Utility
			static std::tuple<unsigned, unsigned> getWindowSize();
			static float getTime();
			static void doKeypress(std::string k);
			static void logMsg(std::string m);
			
			// World
			static bool addScript(std::string s);
			static bool removeScript(std::string s);
			static Entity* newEntity();
			static bool removeEntity(int e);
			static std::vector<Entity*> getEntities();
			static Entity* getEntity(int e);
			static Entity* getPlayer();
			static bool isAround(Physical* p, float x, float y, float r);
			static std::tuple<int, int> getWorldSize();
			static std::string getCurrentWorld();
		
			// Entity System
			static bool add(Entity* e, std::string c);
			static bool remove(Entity* e, std::string c);
			static bool has(Entity* e, std::string c);
			
			// Drawable
			static Drawable* getDrawable(Entity* e);
			static bool setTexture(Drawable* d, std::string t);
			static void setTextureRect(Drawable* d, int x, int y, int w, int h);
			static std::tuple<float, float> getSpriteSize(Drawable* d);
			static void setScale(Drawable* d, float x, float y);
			
			// Movable
			static Movable* getMovable(Entity* e);
			static void setMoveVelocity(Movable* m, float v);
			static std::tuple<float, float> getVelocity(Movable* m);
			
			// Physical
			static Physical* getPhysical(Entity* e);
			static void setPosition(Physical* p, float x, float y);
			static std::tuple<float, float> getPosition(Physical* p);
			static void setSize(Physical* p, unsigned x, unsigned y);
			static std::tuple<unsigned, unsigned> getSize(Physical* p);
			
			// Name
			static Name* getName(Entity* e);
			static void setName(Name* n, std::string name);
			static std::string getNameVal(Name* n);
			
			// Noisy
			static Noisy* getNoisy(Entity* e);
			static void setSound(Noisy* n, std::string s);
			static std::string getSound(Noisy* n);
			
			// Settings
			static std::tuple<bool, std::string> getSettingStr(std::string s);
			static std::tuple<bool, bool> getSettingBool(std::string s);
			static std::tuple<bool, float> getSettingNum(std::string s);
	};
}

#endif // SCRIPT_HPP
