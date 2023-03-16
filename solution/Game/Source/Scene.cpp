#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	//L02: DONE 3: Instantiate the player using the entity manager

	for (pugi::xml_node playerNode = config.child("player"); playerNode; playerNode = playerNode.next_sibling("player"))
	{
		Player* player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
		player->parameters = playerNode;

		players.Add(player);

	}
	
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	CreateCameras(DisplayType::FOUR_SCREENS, app->render);
	
	// L03: DONE: Load map
	bool retLoad = app->map->Load();

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::CreateCameras(DisplayType display, Render* render)
{
	switch (display)
	{
	case DisplayType::ONE_SCREEN:

		render->AddCamera({ 0, 0 }, { 0, 0, 1280, 720 });

		break;

	case DisplayType::TWO_HORIZONTAL:

		render->AddCamera({ 0, 0 }, { 2, 2, 1276, 357 });
		render->AddCamera({ 0, 0 }, { 2, 361, 1276, 357 });

		break;

	case DisplayType::TWO_VERTICAL:

		render->AddCamera({ 0, 0 }, { 2, 2, 637, 716 });
		render->AddCamera({ 0, 0 }, { 641, 2, 637, 716 });

		break;

	case DisplayType::THREE_LEFT:

		render->AddCamera({ 0, 0 }, { 2, 2, 637, 357 });
		render->AddCamera({ 0, 0 }, { 641, 2, 637, 357 });
		render->AddCamera({ 0, 0 }, { 2, 361, 637, 357 });

		break;

	case DisplayType::THREE_CENTERED:

		render->AddCamera({ 0, 0 }, { 2, 2, 637, 357 });
		render->AddCamera({ 0, 0 }, { 641, 2, 637, 357 });
		render->AddCamera({ 0, 0 }, { 321, 361, 637, 357 });

		break;

	case DisplayType::THREE_RIGHT:

		render->AddCamera({ 0, 0 }, { 2, 2, 637, 357 });
		render->AddCamera({ 0, 0 }, { 641, 2, 637, 357 });
		render->AddCamera({ 0, 0 }, { 641, 361, 637, 357 });

		break;

	case DisplayType::FOUR_SCREENS:

		render->AddCamera({ 0, 0 }, { 2, 2, 637, 357 });
		render->AddCamera({ 0, 0 }, { 641, 2, 637, 357 });
		render->AddCamera({ 0, 0 }, { 2, 361, 637, 357 });
		render->AddCamera({ 0, 0 }, { 641, 361, 637, 357 });

		break;

	}
}
