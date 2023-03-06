#include "App.h"
#include "Window.h"
#include "Render.h"
#include "Input.h"

#include "Defs.h"
#include "Log.h"

#define VSYNC true

Render::Render() : Module()
{
	name.Create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
Render::~Render()
{}

// Called before render is available
bool Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;

	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if (config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(app->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//initialise the SDL_ttf library
	TTF_Init();

	//load a font into memory
	font = TTF_OpenFont("Assets/Fonts/arial/arial.ttf", 25);

	return ret;
}

// Called before the first frame
bool Render::Start()
{
	LOG("render start");
	// back background
	//SDL_RenderGetViewport(renderer, &viewport);

	ListItem<Camera*>* item = cameras.start;
	for (; item != nullptr; item = item->next)
	{
		SDL_RenderGetViewport(renderer, &item->data->GetViewport());
	}

	return true;
}

// Called each loop iteration
bool Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool Render::Update(float dt)
{
	float speed = 0.2 * dt;

	ListItem<Camera*>* item = app->render->cameras.start;
	for (; item != nullptr; item = item->next)
	{
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			item->data->pos.y -= ceil(speed);

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			item->data->pos.y += ceil(speed);

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			item->data->pos.x -= ceil(speed);

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			item->data->pos.x += ceil(speed);

		if (item->data->pos.x <= 0) item->data->pos.x = 0;
		if (item->data->pos.y <= 0) item->data->pos.y = 0;
		if (item->data->pos.x + item->data->viewport.w >= 2048) item->data->pos.x = 2048 - item->data->viewport.w;
		if (item->data->pos.y + item->data->viewport.h >= 768) item->data->pos.y = 768 - item->data->viewport.h;

	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		app->render->cameras.At(0)->data->pos.y -= ceil(speed);

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		app->render->cameras.At(0)->data->pos.y += ceil(speed);

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		app->render->cameras.At(0)->data->pos.x -= ceil(speed);

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		app->render->cameras.At(0)->data->pos.x += ceil(speed);

	return true;
}

bool Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool Render::CleanUp()
{
	cameras.Clear();

    // Free the font
	TTF_CloseFont(font);

	//we clean up TTF library
	TTF_Quit();


	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

void Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void Render::SetViewPort(const SDL_Rect& rect)
{
	//SDL_RenderSetViewport(renderer, &rect);

	ListItem<Camera*>* item = cameras.start;
	for (; item != cameras.end; item = item->next)
	{
		SDL_RenderSetViewport(renderer, &item->data->GetViewport());
	}

}

void Render::ResetViewPort()
{
	//SDL_RenderSetViewport(renderer, &viewport);

	ListItem<Camera*>* item = cameras.start;
	for (; item != cameras.end; item = item->next)
	{
		SDL_RenderSetViewport(renderer, &item->data->GetViewport());
	}

}

void Render::AddCamera(iPoint bounds, SDL_Rect viewport)
{
	Camera* camera = new Camera(bounds, viewport);

	cameras.Add(camera);
}

void Render::ClearCameras()
{
	cameras.Clear();
}

Camera* Render::GetCamera()
{
	ListItem<Camera*>* item = cameras.start;
	for (; item != nullptr; item = item->next)
	{
		if (item->data->assigned == false)
		{
			item->data->assigned = true;
			return item->data;
		}
	}
}

// Blit to screen
bool Render::DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivotX, int pivotY) const
{
	bool ret = true;
	SDL_Rect rect = { 0,0,0,0 };
	ListItem<Camera*>* it = cameras.start;
	for (; it != nullptr; it = it->next)
	{
		// TODO 5: Here you have the x and y that you receive in the function. You also have to use
		// the camera position and the viewport and also the speed.

		rect.x = (int)((-it->data->GetPos().x + it->data->GetViewport().x) * speed) + x * app->win->scale;
		rect.y = (int)((-it->data->GetPos().y + it->data->GetViewport().y) * speed) + y * app->win->scale;
		SDL_Rect cam = it->data->GetViewport();
		if (section != NULL)
		{
			rect.w = section->w;
			rect.h = section->h;
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		}

		// TODO 6: Check if the rect is inside of the viewport or not. If not, you don't want to draw it

		if (rect.x + rect.w > cam.x && rect.x < cam.x + cam.w &&
			rect.y + rect.h > cam.y && rect.y < cam.y + cam.h)
		{
			if (rect.x < cam.x)
				rect.x = cam.x;
			if (rect.y < cam.y)
				rect.y = cam.y;
			if (rect.x + rect.w > cam.x + cam.w)
				rect.w = (cam.x + cam.w) - rect.x;
			if (rect.y + rect.h > cam.y + cam.h)
				rect.h = (cam.y + cam.h) - rect.y;

			rect.w *= app->win->scale;
			rect.h *= app->win->scale;

			SDL_Point* p = NULL;
			SDL_Point pivot;

			if (pivotX != INT_MAX && pivotY != INT_MAX)
			{
				pivot.x = pivotX;
				pivot.y = pivotY;
				p = &pivot;
			}
			if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
			{
				LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
				ret = false;
			}
		}
	}

	return ret;
}

bool Render::DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;

	for (ListItem<Camera*>* it = cameras.start; it != nullptr; it = it->next)
	{
		SDL_Rect cam = it->data->GetViewport();
		SDL_Rect rec(rect);
		if (use_camera)
		{
			// TODO 5: Here you have the x and y from the rect that you receive in the function. You also have to use
			// the camera position and the viewport and also the speed.

			rec.x = (int)((rect.x + (it->data->GetViewport().x - it->data->GetPos().x)) * app->win->scale);
			rec.y = (int)((rect.y + (it->data->GetViewport().y - it->data->GetPos().y)) * app->win->scale);
			rec.w *= app->win->scale;
			rec.h *= app->win->scale;
		}

		// TODO 6: Check if the rect is inside of the viewport or not. If not, you don't want to draw it

		if (rec.x + rec.w > cam.x && rec.x < cam.x + cam.w &&
			rec.y + rec.h > cam.y && rec.y < cam.y + cam.h)
		{
			if (rec.x < cam.x)
				rec.x = cam.x;
			if (rec.y < cam.y)
				rec.y = cam.y;
			if (rec.x + rec.w > cam.x + cam.w)
				rec.w = (cam.x + cam.w) - rec.x;
			if (rec.y + rec.h > cam.y + cam.h)
				rec.h = (cam.y + cam.h) - rec.y;

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, r, g, b, a);

			int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

			if (result != 0)
			{
				LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
				ret = false;
			}
		}
	}

	return ret;
}

bool Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;

	for (ListItem<Camera*>* it = cameras.start; it != nullptr; it = it->next)
	{
		uint scale = app->win->GetScale();

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);

		int result = -1;

		if (use_camera)
			result = SDL_RenderDrawLine(renderer, it->data->GetPos().x + x1 * scale, it->data->GetPos().y + y1 * scale, it->data->GetPos().x + x2 * scale, it->data->GetPos().y + y2 * scale);
		else
			result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

		if (result != 0)
		{
			LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
			ret = false;
		}

	}
	return ret;
}

bool Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	for (ListItem<Camera*>* it = cameras.start; it != nullptr; it = it->next)
	{
		uint scale = app->win->GetScale();

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);

		int result = -1;
		SDL_Point points[360];

		float factor = (float)M_PI / 180.0f;

		for (uint i = 0; i < 360; ++i)
		{
			points[i].x = (int)(it->data->GetPos().x + x + radius * cos(i * factor));
			points[i].y = (int)(it->data->GetPos().y + y + radius * sin(i * factor));
		}

		result = SDL_RenderDrawPoints(renderer, points, 360);

		if (result != 0)
		{
			LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
			ret = false;
		}
	}
	return ret;
}

bool Render::DrawText(const char* text, int posx, int posy,int w,int h, SDL_Color color) {

	for (ListItem<Camera*>* it = cameras.start; it != nullptr; it = it->next)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		SDL_Rect dstrect = { posx, posy, w, h };

		SDL_RenderCopy(renderer, texture, NULL, &dstrect);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}
	return true;
}

//// L03: DONE 6: Implement a method to load the state
//// for now load camera's x and y
//bool Render::LoadState(pugi::xml_node& data)
//{
//	camera.x = data.child("camera").attribute("x").as_int();
//	camera.y = data.child("camera").attribute("y").as_int();
//
//	return true;
//}
//
//// L03: DONE 8: Create a method to save the state of the renderer
//// using append_child and append_attribute
//bool Render::SaveState(pugi::xml_node& data)
//{
//	pugi::xml_node cam = data.append_child("camera");
//
//	cam.append_attribute("x") = camera.x;
//	cam.append_attribute("y") = camera.y;
//
//	return true;
//}
