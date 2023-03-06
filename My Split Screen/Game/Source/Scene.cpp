#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Map.h"
#include "PathFinding.h"
#include "GuiManager.h"

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
	if (config.child("player")) {
		player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
		player->parameters = config.child("player");
	}
	
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	CreateCameras(DisplayType::FOUR_SCREENS, app->render);
	
	// L03: DONE: Load map
	bool retLoad = app->map->Load();

	map = app->tex->Load("Assets/Textures/SimpleMap.png");

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

	//app->render->DrawTexture(map,0,0);

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

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	// L15: DONE 5: Implement the OnGuiMouseClickEvent method
	LOG("Event by %d ",control->id);

	switch (control->id)
	{
	case 1:
		LOG("Button 1 click");
		break;
	case 2:
		LOG("Button 2 click");
		break;
	}

	return true;
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
