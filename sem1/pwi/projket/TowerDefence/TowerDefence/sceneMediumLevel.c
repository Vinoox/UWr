#include "sceneLevel.h"
#include "sceneMenu.h"
#include "tower.h"


static ALLEGRO_BITMAP* background;
static ALLEGRO_BITMAP* moneyBg;
static ALLEGRO_BITMAP* backBg;
static ALLEGRO_TIMER* timer;
static Button backBtn;
static int map[10][10];
struct Bullet* bullet = NULL;
static Enemy* enemy = NULL;
static Toolbar* toolbar = NULL;
static Tower* tower = NULL;
static Point* start = NULL;
extern int gameMoney;
extern int gameLife;
extern ALLEGRO_FONT* font;
static int prevTimer = 0;
static int tickIdx = 0;

static void init();
static void draw();
static void destroy();
static void onMouseDown(int btn, int x, int y, int dz);
static void tick();
static void update();

static void init() {
	prevTimer = 0;
	tickIdx = 0;
	gameMoney = 200;
	gameLife = 1000;
	background = al_load_bitmap("mapypng/mapa2/najnowsze/mapa2_przeszkody10x10.png");
	if (!background) gameCrashLog("blad ladowania pliku mapa2");
	moneyBg = al_load_bitmap("przyciski/moneyBackground.png");
	if (!moneyBg) gameCrashLog("blad ladowania pliku moneyBackground.png");
	timer = al_create_timer(1);
	backBg = al_load_bitmap("przyciski/back.png");
	if (!backBg) gameCrashLog("blad ladowania pliku backBtn.png");
	timer = al_create_timer(1);
	if (!timer) gameCrashLog("blad inicjalizacji timera w sceneEasyLevel.c");
	al_start_timer(timer);
	backBtn = (Button){ 1765, 25, 128, 128 };
	getMap(map, 2);
	toolbar = toolbarInit();
	start = getPoints("sciezkitxt/sciezka2.txt");
	gameLog("%d %d", start->x, start->y);
	enemy = newEnemy(enemy, "przeciwnicy/czolg_zielony.png", start, 100);
	bullet = bulletInit();
}

static void draw() {
	al_draw_bitmap(background, 0, 0, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 200, 0, ALLEGRO_ALIGN_CENTRE, "czas fali: %d", 200 - al_get_timer_count(timer));
	al_draw_textf(font, al_map_rgb(0, 0, 0), 200, 45, ALLEGRO_ALIGN_CENTRE, "zycie: %d", gameLife);
	al_draw_scaled_bitmap(moneyBg,
		0, 0, 64, 64,
		60, 100, 256, 64, 0);
	al_draw_textf(font, al_map_rgb(0, 0, 0), 188, 105, ALLEGRO_ALIGN_CENTRE, "%d", gameMoney);
	al_draw_scaled_bitmap(backBg,
		0, 0, 64, 64,
		backBtn.x, backBtn.y, 128, 128, 0);
	if (bullet->active == true) {
		bullet = bulletDraw(bullet);
	}
	toolbarDraw(toolbar);
	tower = towerDraw(tower, enemy, bullet);
	if (bullet->active == true) {
		bullet = delLeftBullets(bullet);
	}
	enemy = enemyDraw(enemy);
	if (gameLife <= 0) {
		al_draw_textf(font, al_map_rgb(0, 0, 0), 1000, 500, ALLEGRO_ALIGN_CENTRE, "Przegrana!");
		al_set_timer_count(timer, 200);
	}
	else if (al_get_timer_count(timer) > 200) {
		al_draw_textf(font, al_map_rgb(0, 0, 0), 1000, 500, ALLEGRO_ALIGN_CENTRE, "Zwyciestwo!");
	}
	if (al_get_timer_count(timer) > 205) {
		gameSceneChange(sceneMenuCreate());
	}
}

static void destroy() {
	al_destroy_bitmap(background);
	al_destroy_bitmap(moneyBg);
	al_destroy_timer(timer);
	tower = delAllTowers(tower);
	if (bullet->active == true) {
		bullet = delAllBullets(bullet);
	}
	enemy = delAllEnemies(enemy);
}

static void onMouseDown(int btn, int x, int y, int dz) {
	mouseClickToolbar(toolbar, x, y);
	if (buttonPresed(backBtn, (MousePos) { x, y }))
	{
		gameSceneChange(sceneMenuCreate());
		gameLog("przycisk powrot wcisniety");
	}
	switch (toolbar->status) {
	case 1:
		tower = towerFunction(map, 1, x, y, tower, 1, &gameMoney);
		break;
	case 2:
		tower = towerFunction(map, 2, x, y, tower, 1, &gameMoney);
		break;
	case 3:
		tower = towerFunction(map, 1, x, y, tower, 2, &gameMoney);
		break;
	case 4:
		tower = towerFunction(map, 1, x, y, tower, 3, &gameMoney);
		break;
	}
}

static void tick(void) {
	if (tickIdx < 50 && tickIdx % 5 == 0) {
		enemy = newEnemy(enemy, "przeciwnicy/czolg_zielony.png", start, 100);
	}
	if (tickIdx > 20 && tickIdx < 190 && tickIdx % 3 == 0) {
		enemy = newEnemy(enemy, "przeciwnicy/czolg_zielony.png", start, 300);
	}
	if (tickIdx > 50 && tickIdx < 190 && tickIdx % 5 == 0) {
		enemy = newEnemy(enemy, "przeciwnicy/czolg_szary.png", start, 300);
	}
	if (tickIdx > 80 && tickIdx < 190 && tickIdx % 4 == 0) {
		enemy = newEnemy(enemy, "przeciwnicy/czolg_szary.png", start, 300);
	}
	if (tickIdx > 100 && tickIdx < 190 && tickIdx % 10 == 0) {
		enemy = newEnemy(enemy, "przeciwnicy/czolg_czerwony.png", start, 800);
	}
	if (tickIdx > 150 && tickIdx < 190 && tickIdx % 155 == 0) {
		enemy = newEnemy(enemy, "przeciwnicy/czolg_czarny.png", start, 2000);
	}
	tickIdx++;
}

static void update() {
	if (prevTimer != al_get_timer_count(timer)) {
		tick();
		prevTimer = al_get_timer_count(timer);
	}
}

Scene sceneMediumLevelCreate()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Poziom drugi";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.onMouseDown = &onMouseDown;
	scene.update = &update;
	return scene;
}

