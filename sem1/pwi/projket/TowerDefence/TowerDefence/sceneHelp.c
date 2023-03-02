#include "sceneMenu.h"

static ALLEGRO_BITMAP* background;
static ALLEGRO_BITMAP* przycisk;
static Button backBtn;

static void init() {
	background = al_load_bitmap("instrukcja/JAK_GRAC.png");
	if (!background) gameCrashLog("blad ladowania pliku JAK_GRAC.png");
	przycisk = al_load_bitmap("przyciski/back.png");
	if (!przycisk) gameCrashLog("blad ladowania pliku back.png");
	backBtn = (Button){ 1765, 25, 128, 128 };
	//.getMap("mapa1.txt");
}

static void draw() {
	al_draw_bitmap(background, 0, 0, 0);
	al_draw_scaled_bitmap(przycisk,
		0, 0, 64, 64,
		backBtn.x, backBtn.y, 128, 128, 0);
}

static void onMouseDown(int btn, int x, int y, int dz) {
	if (buttonPresed(backBtn, (MousePos) { x, y }))
	{
		gameSceneChange(sceneMenuCreate());
		gameLog("przycisk powrot wcisniety");
	}
}

static void destroy() {
	al_destroy_bitmap(background);
	al_destroy_bitmap(przycisk);
}

Scene sceneHelpCreate()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Jak grac";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.onMouseDown = &onMouseDown;
	return scene;
}

