#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

struct constants {
	static constexpr int window_width{ 430 };
	static constexpr int window_height{ 792 };
	static constexpr int block_width{ 36 };
	static constexpr int block_height{ 36 };
	static constexpr int rows{ 20 };
	static constexpr int columns{ 10 };
	static constexpr std::array<std::array<int, 8>, 7> tetromino_styles { {
		{4, 0, 3, 0, 2, 0, 1, 0}, // I
		{0, 0, 1, 0, 2, 0, 2, 1}, // L
		{0, 1, 1, 1, 2, 1, 2, 0}, // J
		{0, 1, 1, 1, 1, 0, 2, 0}, // Z
		{0, 0, 1, 0, 1, 1, 2, 1}, // S
		{0, 0, 0, 1, 1, 1, 1, 0}, // O
		{0, 1, 1, 0, 1, 1, 2, 1}  // T
	} };
};

#endif