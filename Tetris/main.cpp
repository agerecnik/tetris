#include "Game.h"
#include <iostream>

int main(int argc, char* argv[]) {

	srand(time(0));
	Game* game = new Game();
	const char* title = "Tetris";
	if (game->init(title)) {
		while (game->isRunning()) {
			game->setCurrentTime(SDL_GetTicks());
			game->handleEvents();
			game->gameplay();
			game->updateRender();
		}
	}
	else {
		std::cout << "Failed to initialize";
	}
	game->clean();

	return 0;
}