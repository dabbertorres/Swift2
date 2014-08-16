#include "../src/Game.hpp"

int main(int argc, char **argv)
{
	swift::Game game;
	
	game.Start(argc, argv);
	
	game.GameLoop();
	
	game.Finish();
	
	return 0;
}
