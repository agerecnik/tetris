#ifndef FIELD_H
#define FIELD_H

#include "entity.h"
#include <array>

class Field : public Entity {
	std::array<std::array<int, constants::columns>, constants::rows> field { 0 };

public:
	Field() {};
	Field(SDL_Texture* t) : Entity(t) {}

	void updateRender(SDL_Renderer* renderer) override;
	void setPosition(const int& x, const int& y, const int& color);
	int getPosition(const int& x, const int& y);
	void update();
};

#endif