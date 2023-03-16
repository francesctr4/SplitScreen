#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	//L02: DONE 1: Initialize Player parameters

	//L02: DONE 5: Get Player parameters from XML
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	id = parameters.attribute("id").as_int();

	if (SString(parameters.attribute("keys").as_string()) == SString("wasd")) keys = InputKeys::WASD;
	if (SString(parameters.attribute("keys").as_string()) == SString("tfgh")) keys = InputKeys::TFGH;
	if (SString(parameters.attribute("keys").as_string()) == SString("ijkl")) keys = InputKeys::IJKL;
	if (SString(parameters.attribute("keys").as_string()) == SString("arrows")) keys = InputKeys::ARROWS;

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	// L07 DONE 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateCircle(position.x+16, position.y+16, 16, bodyType::KINEMATIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this; 

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::PLAYER;

	//initialize audio effect - !! Path is hardcoded, should be loaded from config.xml
	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");

	return true;
}

bool Player::Update()
{

	// L07 DONE 5: Add physics to the player - updated player position using physics

	int speed = 5; 
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y); 

	//L02: DONE 4: modify the position of the player using arrow keys and render the texture

	HandleInput(keys, vel, speed);

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	app->render->DrawTexture(texture, position.x , position.y);

	return true;
}

bool Player::CleanUp()
{
	return true;
}

// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
		case ColliderType::ITEM:
			LOG("Collision ITEM");
			app->audio->PlayFx(pickCoinFxId);
			break;
		case ColliderType::PLATFORM:
			LOG("Collision PLATFORM");
			break;
		case ColliderType::UNKNOWN:
			LOG("Collision UNKNOWN");
			break;
	}

}

void Player::HandleInput(InputKeys keys, b2Vec2& vel, int speed) {

	if (id <= app->render->cameras.Count()) {

		if (keys == InputKeys::WASD) {

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, -speed);
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, speed);
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) vel = b2Vec2(-speed, -GRAVITY_Y);
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) vel = b2Vec2(speed, -GRAVITY_Y);

		}

		if (keys == InputKeys::TFGH) {

			if (app->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, -speed);
			if (app->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, speed);
			if (app->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) vel = b2Vec2(-speed, -GRAVITY_Y);
			if (app->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT) vel = b2Vec2(speed, -GRAVITY_Y);

		}

		if (keys == InputKeys::IJKL) {

			if (app->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, -speed);
			if (app->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, speed);
			if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) vel = b2Vec2(-speed, -GRAVITY_Y);
			if (app->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) vel = b2Vec2(speed, -GRAVITY_Y);

		}

		if (keys == InputKeys::ARROWS) {

			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, -speed);
			if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) vel = b2Vec2(GRAVITY_X, speed);
			if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) vel = b2Vec2(-speed, -GRAVITY_Y);
			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) vel = b2Vec2(speed, -GRAVITY_Y);

		}

	}

}
