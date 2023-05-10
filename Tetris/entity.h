#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <SDL_image.h>
#include "constants.h"

class Entity {
protected:
	SDL_Texture* texture = NULL;
	SDL_Rect src_rect = { 0, 0, constants::block_width, constants::block_height },
		dst_rect = { 0, 0, constants::block_width, constants::block_height };

public:
	Entity() {}
	Entity(SDL_Texture* t) : texture(t) {}

	virtual void updateRender(SDL_Renderer* renderer) = 0;
	void setRectPos(SDL_Rect& rect, const int& x, const int& y, const int& w, const int& h) noexcept;
	void moveRectPos(SDL_Rect& rect, const int& x, const int& y) noexcept;
	
	virtual ~Entity() {}
};

#endif