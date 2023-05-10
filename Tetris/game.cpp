#include <iostream>
#include "game.h"

bool Game::init(const char* title) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::window_width, constants::window_height, SDL_WINDOW_SHOWN);
		if (window != NULL) {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer != NULL) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				int img_flags = IMG_INIT_PNG;
				int initted = IMG_Init(img_flags);
				if ((initted & img_flags) != img_flags) {
					std::cout << "Failed to init required png support \n" << "IMG_Init() Error: " << IMG_GetError() << std::endl;
				}
				SDL_Surface* surface = IMG_Load("resources/background.png");
				background = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);
				surface = IMG_Load("resources/blocks.png");
				blocks = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);

				TTF_Init();
				font = TTF_OpenFont("resources/verdana.ttf", 70);
				surface = TTF_RenderText_Solid(font, "Game Over", { 0, 0, 0 });
				game_over_message = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);

				field = Field{ blocks };
				nextTetromino();
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	running = true;
	return true;
}

void Game::setCurrentTime(const Uint32& t) noexcept {
	current_time = t;
}

bool Game::isRunning() noexcept {
	return running;
}

void Game::nextTetromino() {
	int color = 1 + rand() % 7;
	int n = rand() % 7;
	current_tetromino_state = Tetromino(blocks, constants::tetromino_styles[n], color);
	std::array<SDL_Point, 4> points = current_tetromino_state.getPoints();
	for (int i = 0; i < 4; ++i) {
		if (field.getPosition(points[i].x, points[i].y)) {
			game_over = true;
			break;
		}
	}
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				rotate = true;
				break;
			case SDLK_LEFT:
				dx = -1;
				break;
			case SDLK_RIGHT:
				dx = 1;
				break;
			case SDLK_r:
				reset();
			default:
				break;
			}
		default:
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_DOWN]) {
		delay = 50;
	}
}

bool Game::isTetrominoValid() {
	std::array<SDL_Point, 4> current_tetromino_points = current_tetromino_state.getPoints();
	for (int i = 0; i < 4; ++i) {
		if (current_tetromino_points[i].x < 0 || current_tetromino_points[i].x >= constants::columns || current_tetromino_points[i].y < 0 || current_tetromino_points[i].y >= constants::rows) {
			return false;
		}
		else if (field.getPosition(current_tetromino_points[i].x, current_tetromino_points[i].y)) {
			return false;
		}
	}
	return true;
}

void Game::gameplay() {
	if (!game_over) {
		previous_tetromino_state = current_tetromino_state;

		if (dx) {
			current_tetromino_state.translateX(dx);
			if (!isTetrominoValid()) {
				current_tetromino_state = previous_tetromino_state;
			}
		}

		if (rotate) {
			current_tetromino_state.rotate();
			if (!isTetrominoValid()) {
				current_tetromino_state = previous_tetromino_state;
			}
		}

		if (current_time - start_time > delay) {
			previous_tetromino_state = current_tetromino_state;
			current_tetromino_state.translateY(1);
			if (!isTetrominoValid()) {
				std::array<SDL_Point, 4> previous_tetrimino_points = previous_tetromino_state.getPoints();
				for (int i = 0; i < 4; ++i) {
					int c = previous_tetromino_state.getColor();
					field.setPosition(previous_tetrimino_points[i].x, previous_tetrimino_points[i].y, c);
				}
				field.update();
				nextTetromino();
			}
			start_time = current_time;
		}
	}
	dx = 0;
	rotate = false;
	delay = 300;

}

void Game::updateRender() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	field.updateRender(renderer);
	current_tetromino_state.updateRender(renderer);
	if (game_over) {
		SDL_RenderCopy(renderer, game_over_message, NULL, &message_rect);
	}
	SDL_RenderPresent(renderer);
}

void Game::reset() {
	game_over = false;
	field = Field{ blocks };
	nextTetromino();
	start_time = current_time;
}

void Game::clean() {
	SDL_DestroyTexture(blocks);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(game_over_message);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}