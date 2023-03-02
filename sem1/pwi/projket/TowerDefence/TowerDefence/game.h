#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <string.h>


#define LOG_ENABLED true

typedef void(*funcPtr)(void);
typedef void(*funcPtrKeyboard)(int keycode);
typedef bool(*funcPtrQuit)(void);
typedef void(*funcPtrMouse)(int btn, int x, int y, int dz);

typedef struct {
	char* name;
	funcPtr initialize;
	funcPtr update;
	funcPtr draw;
	funcPtr destroy;
	funcPtrQuit quit;
	funcPtrKeyboard onKeyDown;
	funcPtrKeyboard onKeyUp;
	funcPtrMouse onMouseDown;
	funcPtrMouse onMouseMove;
	funcPtrMouse onMouseUp;
	funcPtrMouse onMouseScroll;
} Scene;

typedef struct {
	int x, y;
} MousePos;

typedef struct {
	int x, y, w, h;
} Button;


typedef struct {
	ALLEGRO_BITMAP* bitmapArray[5];
	short int status, widthAndHeight;
	float initialHeight;
} Toolbar;

typedef struct node {
	ALLEGRO_BITMAP* towerPicture;
	struct node* nextTower;
	short int x, y, towerType, towerlvl, timer, cooldown;
	bool canShoot;
	int towerRange;
	double degrees;
} Tower;

typedef struct point {
	int x, y;
	struct Point* nextPoint;
} Point;

typedef struct enemy {
	ALLEGRO_BITMAP* enemyPicture;
	int x, y;
	Point* point;
	double degrees;
	int width, height;
	int hp;
	int damage;
	struct enemy* nextEnemy;
	bool active;
} Enemy;

typedef struct Bullet {
	ALLEGRO_BITMAP* bulletPicture;
	short int x, y;
	struct Bullet* nextBullet;
	Enemy* target;
	double degrees;
	int width, height, damage, bulletType;
	bool active;
};

// definicja stałych systemowych
extern const int FPS;
extern const int SCREEN_W;
extern const int SCREEN_H;


// definicja zmiennych
extern Scene activeScene;
// 1 - LPM, 2 - PPM, 3 ŚPM.
//extern bool* mouseState;
extern int mouseX, mouseY;
extern ALLEGRO_FONT* font;
extern int gameMoney;
extern int gameLife;


// prototypy funckji
void gameStart(void);
void gameSceneChange(Scene nextScene);
void gameDestroy(void);
void gameMainLoop(void);
bool buttonPresed(Button btn, MousePos mouse);

// funkcje troche jak printf tylko że do pliku log
void gameCrashLog(const char* format, ...);
void gameLog(const char* format, ...);
void gameWriteLog(const char* format, va_list arg, int type);

// funkcje do inicjalizacji i usuwania zmiennych globalnych
//extern void globalInit(void);
//extern void globalFree(void);

