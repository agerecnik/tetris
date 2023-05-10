#ifndef TETRIS_H
#define TETRIS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>

#include "constants.h"
#include "tetromino.h"
#include "field.h"

class Game {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* background = NULL, *blocks = NULL;
	TTF_Font* font = NULL;
	SDL_Texture* game_over_message = NULL;
	SDL_Rect message_rect = {constants::window_width / 2 - 100, constants::window_height / 2 - 50, 200, 100};

	bool running = false;
	bool game_over = false;
	Field field;
	Tetromino current_tetromino_state, previous_tetromino_state;
	int dx = 0;
	bool rotate = false;
	unsigned int delay = 300;
	Uint32 start_time = 0, current_time = 0;

	void nextTetromino();
	bool isTetrominoValid();
	void reset();

public:
	Game() {}

	bool init(const char* title);
	void setCurrentTime(const Uint32& t) noexcept;
	bool isRunning() noexcept;
	void handleEvents();
	void gameplay();
	void updateRender();
	void clean();
};
#endif