#include "game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//typedef struct point {
//	int x, y;
//	struct Point* nextPoint;
//} Point;
//
//typedef struct enemy{
//	ALLEGRO_BITMAP* enemyPicture;
//	int x, y;
//	Point* point;
//	double degrees;
//	int width, height;
//	int hp;
//	struct Enemy* nextEnemy;
//} Enemy;

Point* createPoint(int a, int b);
Point* newPoint(Point* rootPoint, int a, int b);
Enemy* createEnemy(char* path, Point* start, int hp);
Enemy* newEnemy(Enemy* rootEnemy, char* path, Point* start, int hp);
Enemy* enemyDraw(Enemy* rootEnemy);
Enemy* checkHp(Enemy* rootEnemy);
Enemy* deleteEnemy(Enemy* rootEnemy);
Enemy* delAllEnemies(Enemy* root);
Point* getPoints(char* path);