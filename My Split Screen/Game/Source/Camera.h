#pragma once

#include "SDL/include/SDL.h"
#include "Point.h"

class Camera
{
public:
	Camera(iPoint b, SDL_Rect view) : pos(b), viewport(view), assigned(false) {}

	virtual ~Camera() {}

	inline SDL_Rect GetViewport() { return viewport; }

	inline iPoint GetPos() { return pos; }

	iPoint pos;
	SDL_Rect viewport;

	bool assigned;
};
