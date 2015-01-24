#ifndef THEGAME_HPP
#define THEGAME_HPP

#include "../src/Game.hpp"

#include "GameAssets.hpp"

namespace tg
{
	class TheGame : public swift::Game
	{
		public:
			TheGame();
			~TheGame();

			virtual void start(int c, char** args);

		private:
			virtual void loadAssets();
			virtual void loadMods();
			virtual void initState();
			virtual void initScripting();

			GameAssets assets;
	};
}

#endif // THEGAME_HPP
