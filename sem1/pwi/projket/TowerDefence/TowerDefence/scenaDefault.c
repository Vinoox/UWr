#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "game.h"
#include "scenaDefault.h"

static ALLEGRO_BITMAP* picture;

static void init(char *path);
static void draw();
static void destroy();

void init(char *path)
{
	picture = al_load_bitmap(path);
	if (picture == NULL)
	{
		gameLog("Something is not working...");
	}
}

void draw()
{
	al_draw_bitmap(picture, 0, 0, 0);
}

void destroy()
{
	al_destroy_bitmap(picture);
}

Scene sceneDefaultCreate()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "default";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	return scene;
}
