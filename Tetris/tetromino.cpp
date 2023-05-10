#include "tetromino.h"

Tetromino::Tetromino(SDL_Texture* t, std::array<int, 8> coordinates, int c) : Entity(t), color(c) {
	for (int i = 0; i < points.size(); ++i) {
		points[i].x = coordinates[i * 2];
		points[i].y = coordinates[i * 2 + 1];
	}

}

void Tetromino::updateRender(SDL_Renderer* renderer) {
	for (int i = 0; i < 4; ++i) {
		setRectPos(src_rect, color * constants::block_width, 0, constants::block_width, constants::block_height);
		setRectPos(dst_rect, points[i].x * constants::block_height, points[i].y * constants::block_height, constants::block_width, constants::block_height);
		moveRectPos(dst_rect, constants::block_width, constants::window_height - (constants::rows + 1) * constants::block_height);
		SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
	}
}

void Tetromino::translateX(const int& dx) {
	for (int i = 0; i < 4; ++i) {
		points[i].x += dx;

	}
}

void Tetromino::translateY(const int& dy) {
	for (int i = 0; i < 4; ++i) {
		points[i].y += dy;
	}
}

// Rotate by 90 degrees around arbitrary point:
// x' = -(y - py) + px
// y' = (x - px) + py
void Tetromino::rotate() {
	SDL_Point center_of_rotation = points[2];
	for (int i = 0; i < 4; ++i) {
		int temp_x = points[i].x;
		int temp_y = points[i].y;
		points[i].x = -(temp_y - center_of_rotation.y) + center_of_rotation.x;
		points[i].y = (temp_x - center_of_rotation.x) + center_of_rotation.y;
	}
}

std::array<SDL_Point, 4> Tetromino::getPoints() noexcept {
	return points;
}

int Tetromino::getColor() noexcept {
	return color;
}