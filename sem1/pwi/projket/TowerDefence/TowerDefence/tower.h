#pragma once
#include "game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

void getMap(int* map, int lvl);
struct Bullet *newBullet(struct Bullet* rootBullet, short int x, short int y, Enemy* target, char* path, int bulletType);
struct Bullet* createBullet(short int x, short int y, Enemy* target, char* path, int bulletType);
struct Bullet *bulletDraw(struct Bullet *rootBullet);
struct Bullet* deleteBullet(struct Bullet* rootBullet);
struct Bullet* delLeftBullets(struct Bullet* root);
double getDegrees(int friendX, int friendY, int enemyX, int enemyY);
Toolbar *toolbarInit();
void toolbarDraw(Toolbar* root);
void mouseClickToolbar(Toolbar* root, int x, int y);
Tower *towerFunction(int* map, int towerType, int x, int y, Tower *root, int operationType, int *money);
Tower* newTower(Tower *root, int towerType, int x, int y);
Tower* towerDraw(Tower* root, Enemy *target, struct Bullet* bulletRoot);
Tower* upgradeTower(Tower* root, int x, int y, int* map);
Tower* delTower(Tower* root, int x, int y, int *map, int* money);
double degreesChange(double currentDegrees, double goalDegrees);
Enemy* getTarget(Enemy* targets, int friendX, int friendY, int distance);
Tower* delAllTowers(Tower* root);
struct Bullet* delAllBullets(struct Bullet* root);
struct Bullet* bulletInit();
