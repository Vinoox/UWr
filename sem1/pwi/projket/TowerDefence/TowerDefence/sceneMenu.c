#include "sceneMenu.h"
#include "sceneLevel.h"

static ALLEGRO_BITMAP* background;
static Button easyBtn;
static Button mediumBtn;
static Button hardBtn;
static Button exitBtn;
static Button helpBtn;
static bool running = true;

static void init();
static void draw();
static void destroy();
static void onMouseDown(int btn, int x, int y, int dz);
static bool quit();

static void init() {
	background = al_load_bitmap("starting menu/MENU.png");
	easyBtn = (Button) {590, 505, 245, 90};
	mediumBtn = (Button) {862, 505, 245, 90};
	hardBtn = (Button) {1140, 505, 245, 90};
	exitBtn = (Button) {996, 640, 245, 90};
	helpBtn = (Button){ 723, 640, 245, 90 };
	if (!background) {
		gameCrashLog("blad ladowania pliku menu.png");
	}
}

static void draw() {
	al_draw_bitmap(background, 0, 0, 0);
}

static void destroy() {
	al_destroy_bitmap(background);
}

static void onMouseDown(int btn, int x, int y, int dz) {
	if (buttonPresed(easyBtn, (MousePos) { x, y }))
	{
		gameSceneChange(sceneEasyLevelCreate());
		gameLog("przycisk latwy wcisniety");
	}	
	if (buttonPresed(mediumBtn, (MousePos) { x, y }))
	{
		gameSceneChange(sceneMediumLevelCreate());
		gameLog("przycisk sredni wcisniety");
	}	
	if (buttonPresed(hardBtn, (MousePos) { x, y }))
	{
		gameSceneChange(sceneHardLevelCreate());
		gameLog("przycisk trudny wcisniety");
	}	
	if (buttonPresed(exitBtn, (MousePos) { x, y }))
	{
		running = false;
		gameLog("przycisk wyjscie wcisniety %d", running);
	}	
	if (buttonPresed(helpBtn, (MousePos) { x, y }))
	{
		gameSceneChange(sceneHelpCreate());
		gameLog("przycisk jakGrac wcisniety");
	}

}

static bool quit() {
	return running;
}

Scene sceneMenuCreate()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Menu";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.onMouseDown = &onMouseDown;
	scene.quit = &quit;
	return scene;
	
}
