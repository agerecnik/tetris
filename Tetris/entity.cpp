#include "entity.h"

void Entity::setRectPos(SDL_Rect& rect, const int& x, const int& y, const int& w, const int& h) noexcept {
	rect = { x, y, w, h };
}

void Entity::moveRectPos(SDL_Rect& rect, const int& x, const int& y) noexcept {
	rect.x += x;
	rect.y += y;
}