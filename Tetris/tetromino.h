#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL.h>
#include <array>
#include "entity.h"
#include "constants.h"

class Tetromino : public Entity {
	std::array<SDL_Point, 4> points;
	int color;
	
public:
	Tetromino() {}
	Tetromino(SDL_Texture* t, std::array<int, 8> coordinates, int c);

	void updateRender(SDL_Renderer* renderer) override;
	void translateX(const int& dx);
	void translateY(const int& dy);
	void rotate();
	std::array<SDL_Point, 4> getPoints() noexcept;
	int getColor() noexcept;
};

#endif