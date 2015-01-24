#ifndef GAMESCRIPT_HPP
#define GAMESCRIPT_HPP

#include "../../src/Scripting/Script.hpp"

#include "../../src/Logger/Logger.hpp"

#include "GamePlay.hpp"

namespace tg
{
	class GameScript : public swift::Script
	{
		public:
			GameScript();

			virtual void addVariables();
			virtual void addClasses();
			virtual void addFunctions();
			
			// setters for variables that Lua has access to
			static void setWindow(sf::RenderWindow& win);
			static void setAssetManager(swift::AssetManager& am);
			static void setClock(sf::Clock& c);
			static void setSettings(swift::Settings& s);
			static void setKeyboard(swift::KeyboardManager& k);
			static void setWorld(swift::World& w);
			static void setWorld(std::nullptr_t);
			static void setPlayState(GamePlay& p);
			
			// get world pointer for comparison
			static const swift::World* getWorld();
		
		private:
			// Variables that need to be accessed by Lua
			static sf::RenderWindow* window;
			static swift::AssetManager* assets;
			static sf::Clock* clock;
			static swift::Settings* settings;
			static swift::KeyboardManager* keyboard;
			static swift::World* world;
			static GamePlay* play;
			
			/* Lua converted functions */
			// Utility
			static std::tuple<unsigned, unsigned> getWindowSize();
			static float getTime();
			static void doKeypress(std::string k);
			static void logMsg(std::string m);
			
			// World
			static bool addScript(std::string s);
			static bool removeScript(std::string s);
			static swift::Entity* newEntity();
			static bool removeEntity(int e);
			static std::vector<swift::Entity*> getEntities();
			static swift::Entity* getEntity(int e);
			static swift::Entity* getPlayer();
			static bool isAround(swift::Physical* p, float x, float y, float r);
			static std::string getCurrentWorld();
			static bool setCurrentWorld(std::string s, std::string mf);
			
			// tilemap
			static std::tuple<int, int> getTileSize();
		
			// Entity System
			static bool add(swift::Entity* e, std::string c);
			static bool remove(swift::Entity* e, std::string c);
			static bool has(swift::Entity* e, std::string c);
			
			// Drawable
			static swift::Drawable* getDrawable(swift::Entity* e);
			static bool setTexture(swift::Drawable* d, std::string t);
			static void setTextureRect(swift::Drawable* d, int x, int y, int w, int h);
			static std::tuple<float, float> getSpriteSize(swift::Drawable* d);
			static void setScale(swift::Drawable* d, float x, float y);
			
			// Movable
			static swift::Movable* getMovable(swift::Entity* e);
			static void setMoveVelocity(swift::Movable* m, float v);
			static std::tuple<float, float> getVelocity(swift::Movable* m);
			
			// Physical
			static swift::Physical* getPhysical(swift::Entity* e);
			static void setPosition(swift::Physical* p, float x, float y);
			static std::tuple<float, float> getPosition(swift::Physical* p);
			static void setSize(swift::Physical* p, unsigned x, unsigned y);
			static std::tuple<unsigned, unsigned> getSize(swift::Physical* p);
			
			// Name
			static swift::Name* getName(swift::Entity* e);
			static void setName(swift::Name* n, std::string name);
			static std::string getNameVal(swift::Name* n);
			
			// Noisy
			static swift::Noisy* getNoisy(swift::Entity* e);
			static void setSound(swift::Noisy* n, std::string s);
			static std::string getSound(swift::Noisy* n);
			
			// Settings
			static std::tuple<bool, std::string> getSettingStr(std::string s);
			static std::tuple<bool, bool> getSettingBool(std::string s);
			static std::tuple<bool, float> getSettingNum(std::string s);
	};
}

#endif // GAMESCRIPT_HPP
