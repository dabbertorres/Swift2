#include "../src/Game.hpp"

int main(int argc, char **argv)
{
	swift::Game game("Swift2", 60);
	
	game.start(argc, argv);
	
	game.gameLoop();
	
	game.finish();
	
	return 0;
}
