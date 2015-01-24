#include "src/TheGame.hpp"

#include "src/GamePlay.hpp"
#include "src/GameMenu.hpp"
#include "src/GameSettings.hpp"

int main(int argc, char **argv)
{
	tg::TheGame game;
	
	game.start(argc, argv);
	
	game.gameLoop();
	
	return 0;
}
