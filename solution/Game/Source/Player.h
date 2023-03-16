#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "Physics.h"
#include "SDL/include/SDL.h"

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

	// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
	void OnCollision(PhysBody* physA, PhysBody* physB);

	void HandleInput(InputKeys keys, b2Vec2& vel, int speed);


public:


private:

	//L02: DONE 1: Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;

	int pickCoinFxId;

	int id;
	InputKeys keys;

};

#endif // __PLAYER_H__