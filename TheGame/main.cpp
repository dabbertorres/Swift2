#include "src/TheGame.hpp"

int main(int argc, char** argv)
{
	tg::TheGame game(argc, argv);
	
	game.start();
	
	return 0;
}
