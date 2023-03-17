#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "Physics.h"
#include "SDL/include/SDL.h"

// Split Screen: enum class to manage players input keys
enum class InputKeys {

	WASD,
	TFGH,
	IJKL,
	ARROWS

};

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	// Split Screen: manage players movement
	void HandleInput(InputKeys keys, b2Vec2& vel, int speed);

private:

	// Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// Add physics to the player 
	PhysBody* pbody;

	// Split Screen: attributes to distinguish between players
	int id;
	InputKeys keys;

};

#endif // __PLAYER_H__