#pragma once

#include "SDL/include/SDL.h"
#include "Point.h"

class Camera
{
public:

	// Constructor
	Camera(SDL_Rect view) : viewport(view) {}

	// Destructor
	virtual ~Camera() {}

	// Getters
	inline SDL_Rect GetViewport() const { return viewport; }
	inline iPoint GetPos() const { return pos; }

	// Camera Attributes
	iPoint pos;
	SDL_Rect viewport;

};
