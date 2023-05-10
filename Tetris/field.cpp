#include "field.h"

void Field::updateRender(SDL_Renderer* renderer) {
	for (int i = 0; i < constants::rows; ++i) {
		for (int j = 0; j < constants::columns; ++j) {
			if (field[i][j]) {
				setRectPos(src_rect, field[i][j] * constants::block_width, 0, constants::block_width, constants::block_height);
				setRectPos(dst_rect, j * constants::block_width, i * constants::block_height, constants::block_width, constants::block_height);
				moveRectPos(dst_rect, constants::block_width, constants::window_height - (constants::rows + 1) * constants::block_height);
				SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
			}
		}
	}
}

void Field::setPosition(const int& x, const int& y, const int& color) {
	field[y][x] = color;
}

int Field::getPosition(const int& x, const int& y) {
	return field[y][x];
}

void Field::update() {
	int k = constants::rows - 1;
	for (int i = k; i > 0; --i) {
		int count = 0;
		for (int j = 0; j < constants::columns; ++j) {
			if (field[i][j]) {
				++count;
			}
			field[k][j] = field[i][j];
		}
		if (count < constants::columns) {
			--k;
		}
	}
}