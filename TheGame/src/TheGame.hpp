#ifndef THEGAME_HPP
#define THEGAME_HPP

#include "../src/Game.hpp"

namespace tg
{
	class TheGame : public swift::Game
	{
		public:
			TheGame();
			~TheGame();

			virtual void start(int c, char** args);

		private:
			virtual void initState();
			virtual void initScripting();
	};
}

#endif // THEGAME_HPP
