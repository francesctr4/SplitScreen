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

	// TODO 3 - Split Screen: instantiate the players using the entity manager and add them to the players list.
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
	// TODO 6 - Split Screen: create the necessary cameras to show the chosen DisplayType.
	// Change the DisplayType to control how many screens will be loaded.
	CreateCameras(DisplayType::FOUR_SCREENS);
	
	// Load map
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

// Split Screen: function to create the necessary cameras to display the chosen DisplayType (Hardcoded).
void Scene::CreateCameras(DisplayType display)
{
	switch (display)
	{
	case DisplayType::ONE_SCREEN:

		app->render->AddCamera({ 0, 0, 1280, 720 });

		break;

	case DisplayType::TWO_HORIZONTAL:

		app->render->AddCamera({ 2, 2, 1276, 357 });
		app->render->AddCamera({ 2, 361, 1276, 357 });

		break;

	case DisplayType::TWO_VERTICAL:

		app->render->AddCamera({ 2, 2, 637, 716 });
		app->render->AddCamera({ 641, 2, 637, 716 });

		break;

	case DisplayType::THREE_LEFT:

		app->render->AddCamera({ 2, 2, 637, 357 });
		app->render->AddCamera({ 641, 2, 637, 357 });
		app->render->AddCamera({ 2, 361, 637, 357 });

		break;

	case DisplayType::THREE_CENTERED:

		app->render->AddCamera({ 2, 2, 637, 357 });
		app->render->AddCamera({ 641, 2, 637, 357 });
		app->render->AddCamera({ 321, 361, 637, 357 });

		break;

	case DisplayType::THREE_RIGHT:

		app->render->AddCamera({ 2, 2, 637, 357 });
		app->render->AddCamera({ 641, 2, 637, 357 });
		app->render->AddCamera({ 641, 361, 637, 357 });

		break;

	case DisplayType::FOUR_SCREENS:

		app->render->AddCamera({ 2, 2, 637, 357 });
		app->render->AddCamera({ 641, 2, 637, 357 });
		app->render->AddCamera({ 2, 361, 637, 357 });
		app->render->AddCamera({ 641, 361, 637, 357 });

		break;

	}
}
