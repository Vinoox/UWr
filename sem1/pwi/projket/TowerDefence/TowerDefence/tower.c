#include "tower.h"
#include "game.h"
#include "scenaDefault.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdbool.h>

extern int gameMoney;


void getMap(int* map, int lvl) {
	FILE* ptr;
	if (lvl == 1) {
		ptr = fopen("../resources/mapytxt/mapa1.txt", "r");
	}
	else if (lvl == 2) {
		ptr = fopen("../resources/mapytxt/mapa2.txt", "r");
	}
	else{
		ptr = fopen("../resources/mapytxt/mapa3.txt", "r");
	} 
	if (!ptr)
	{
		gameCrashLog("blad otwarcia pliku mapy w Tower.c");
	}
	char charTemp = fgetc(ptr);
	int i = 0;
	*(map) = 0;
	while(charTemp != EOF)
	{
		if (charTemp >= '0' && charTemp <= '9') {
			*(map + i) = *(map + i) * 10 + charTemp - '0';
		}
		else if (charTemp == '-') {
			*(map + i) = -1;
		}
		else {
			i++;
			*(map + i) = 0;
		}
		charTemp = fgetc(ptr);
	}
}

struct Bullet *createBullet(short int x, short int y, Enemy* target, char *path, int bulletType){
	struct Bullet* temp = (struct Bullet*)malloc(sizeof(struct Bullet));
	al_change_directory("../../../resources");
	temp->bulletPicture = al_load_bitmap(path);
	temp->target = target;
	temp->x = x;
	temp->y = y;
	temp->nextBullet = NULL;
	temp->degrees = 90.0;
	temp->height = al_get_bitmap_height(temp->bulletPicture);
	temp->width = al_get_bitmap_width(temp->bulletPicture);
	temp->bulletType = bulletType;
	if (temp->bulletType == 1) {
		temp->damage = 25;
	}
	else if (temp->bulletType == 2) {
		temp->damage = 35;
	}
	else if (temp->bulletType == 3) {
		temp->damage = 35;
	}
	else {
		temp->damage = 50;
	}
	temp->active = true;
	return temp;
}

struct Bullet *newBullet(struct Bullet* rootBullet, short int x, short int y, Enemy* target, char* path, int bulletType){
	if (rootBullet == NULL){
		rootBullet = createBullet(x, y, target, path, bulletType);
		return rootBullet;
	}
	else if (rootBullet->active == false) {
		al_change_directory("../../../resources");
		rootBullet->bulletPicture = al_load_bitmap(path);
		rootBullet->target = target;
		rootBullet->x = x;
		rootBullet->y = y;
		rootBullet->nextBullet = NULL;
		rootBullet->degrees = 90.0;
		rootBullet->height = al_get_bitmap_height(rootBullet->bulletPicture);
		rootBullet->width = al_get_bitmap_width(rootBullet->bulletPicture);
		rootBullet->bulletType = bulletType;
		if (rootBullet->bulletType == 1) {
			rootBullet->damage = 15;
		}
		else if (rootBullet->bulletType == 2) {
			rootBullet->damage = 25;
		}
		else if (rootBullet->bulletType == 3) {
			rootBullet->damage = 30;
		}
		else {
			rootBullet->damage = 45;
		}
		rootBullet->active = true;
		return rootBullet;
	}
	else {
		rootBullet->nextBullet = newBullet(rootBullet->nextBullet, x, y, target, path, bulletType);
		return rootBullet;
	}
}

struct Bullet *bulletDraw(struct Bullet* rootBullet) {
  	if (rootBullet != NULL && rootBullet->active == true) {
		int xDistance = rootBullet->target->x - rootBullet->x;
		int yDistance = rootBullet->target->y - rootBullet->y;
		int totalDistance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
		if (totalDistance < 5) {
			rootBullet->target->hp -= rootBullet->damage;
			if (rootBullet->target->hp <= 0) {
				rootBullet->target->active = false;
			}
			rootBullet = deleteBullet(rootBullet);
			rootBullet = bulletDraw(rootBullet);
		}
		else{
			al_draw_rotated_bitmap(rootBullet->bulletPicture, rootBullet->width / 2, rootBullet->height / 2, rootBullet->x, rootBullet->y, rootBullet->degrees * 3.14159 / 180, 0);
			int ratio = totalDistance / 5;
			rootBullet->x += xDistance / ratio;
			rootBullet->y += yDistance / ratio;
			rootBullet->degrees = getDegrees(rootBullet->x, rootBullet->y, rootBullet->target->x, rootBullet->target->y);
			rootBullet->nextBullet = bulletDraw(rootBullet->nextBullet);
		}
	}
	return rootBullet;
}

struct Bullet* delLeftBullets(struct Bullet* root, Enemy* target, struct Bullet* mainBullet) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (root->target->active == false) {
			if (root->nextBullet != NULL) {
				struct Bullet* temp = root->nextBullet;
				free(root);
				root = temp;
				root = delLeftBullets(root, target, mainBullet);
			}
			else {
				root->active = false;
				return root;
			}
		}
		else {
			root->nextBullet = delLeftBullets(root->nextBullet, target, mainBullet);
		}
		return root;
	}
}

struct Bullet* deleteBullet(struct Bullet* rootBullet) {
	if (rootBullet->nextBullet == NULL) {
		rootBullet->active = false;
		return rootBullet;
	}
	else {
		struct Bullet* temp = rootBullet->nextBullet;
		free(rootBullet);
		return temp;
	}
}

double getDegrees(int friendX, int friendY, int enemyX, int enemyY)
{
	double segmentX = abs(friendX - enemyX);
	double segmentY = abs(friendY - enemyY);
	if (friendY > enemyY && friendX < enemyX) {
		if (segmentY >= segmentX) {
			return 45.0 * (segmentX / segmentY);
		}
		else { return 90.0 -  45.0 * (segmentY / segmentX); }
	}
	else if (friendY < enemyY && friendX < enemyX) {
		if (segmentX > segmentY) { return 90.0 + 45.0 * (segmentY / segmentX); }
		else{ return 180.0 - 45.0 * (segmentX / segmentY); }
	}
	else if (friendY < enemyY && friendX > enemyX) {
		if (segmentY >= segmentX) {
			return 180.0 + 45.0 * (segmentX / segmentY);
		}
		else { return 270.0 - 45.0 * (segmentY / segmentX); }
	}
	else if (friendY > enemyY && friendX > enemyX) {
		if (segmentX > segmentY) { return 270.0 + 45.0 * (segmentY / segmentX); }
		else { return 360.0 - 45.0 * (segmentX / segmentY); }
	}
	else if (segmentX == 0)
	{
		if (enemyY > friendY) { return 180.0; }
		else { return 0.0; }
	}
	else {
		if (enemyX > friendX) { return 90.0; }
		else { return 270.0; }
	}
}

Toolbar *toolbarInit() {
	Toolbar* temp = (Toolbar *)malloc(sizeof(Toolbar));
	al_change_directory("../../../resources");
	temp->bitmapArray[0] = al_load_bitmap("inne/tower1(128x128).png");
	temp->bitmapArray[1] = al_load_bitmap("inne/tower2(128x128).png");
	temp->bitmapArray[2] = al_load_bitmap("inne/up-arrow(128x128).png");
	temp->bitmapArray[3] = al_load_bitmap("inne/trash(128x128).png");
	temp->bitmapArray[4] = al_load_bitmap("inne/forbidden(128x128).png");
	temp->status = 0;
	temp->widthAndHeight = 128;
	temp->initialHeight = 200.0;
	return temp;
}

void toolbarDraw(Toolbar* root) {
	float height = root->initialHeight;
	for (int i = 0; i < 5; i++) {
		if (i < 4 && root->status == i + 1) {
			al_draw_rectangle(1900 - root->widthAndHeight, height, 1900, height + root->widthAndHeight, al_map_rgb(255, 0, 0), 3.0);
		}
		if (i != 4 || root->status > 0) {
			al_draw_bitmap(root->bitmapArray[i], 1900 - root->widthAndHeight, height, 0);
			height += root->widthAndHeight + 20;
		}
	}
}

void mouseClickToolbar(Toolbar* root, int x, int y) {
	int height = root->initialHeight;
	bool statusChange = false;
	for (int i = 0; i < 4; i++) {
		if (x >= 1900 - root->widthAndHeight && x <= 1900 && y >= height && y <= height + root->widthAndHeight) {
			if (root->status == i + 1) {
				root->status = 0;
			}
			else {
				root->status = i + 1;
			}
			statusChange = true;
			break;
		}
		height += root->widthAndHeight + 20;
	}
	if (statusChange == false) {
		if (x >= 1900 - root->widthAndHeight && x <= 1900 && y >= height && y <= height + root->widthAndHeight) {
			root->status = 0;
		}
	}
}

Tower *towerFunction(int* map, int towerType, int x, int y, Tower *root, int operationType, int *money) {
	if (x >= 447 && x < 1447 && y >= 19 && y < 1019) {
		int mapX = (x - 447) / 99;
		int mapY = (y - 19) / 99;
		switch (operationType) {
		case 1:
			if (*(map + mapX + (10 * mapY)) == 0 && *(money) >= 50) {
				root = newTower(root, towerType, mapX, mapY);
				*(map + mapX + (10 * mapY)) = -(towerType + 1);
				*(money) -= 50;
			}
			break;
		case 2:
			if ((*(map + mapX + (10 * mapY)) == -2 || *(map + mapX + (10 * mapY)) == -3) && *(money) >= 100) {
				root = upgradeTower(root, mapX, mapY, map);
				*(money) -= 100;
			}
			break;
		case 3:
			if (*(map + mapX + (10 * mapY)) < -1) {
				root = delTower(root, mapX, mapY, map, money);
			}
			break;
		}
	}
	return root;
}

Tower* delTower(Tower* root, int x, int y, int *map, int* money) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (root->x == x && root->y == y) {
			if (root->towerlvl == 1) {
				*(money) += 25;
			}
			else {
				*(money) += 75;
			}
			Tower* temp = root->nextTower;
			free(root);
			*(map + x + (10 * y)) = 0;
			return temp;
		}
		else {
			root->nextTower = delTower(root->nextTower, x, y, map, money);
			return root;
		}
	}
}

Tower* newTower(Tower* root, int towerType, int x, int y) {
	if (root == NULL) {
		Tower* temp = (Tower*)malloc(sizeof(Tower));
		al_change_directory("../../../resources");
		if (towerType == 1) {
			temp->towerPicture = al_load_bitmap("inne/tower1(100x100).png");
			temp->towerRange = 200;
			temp->cooldown = 60;
		}
		else {
			temp->towerPicture = al_load_bitmap("inne/tower2(100x100).png");
			temp->towerRange = 400;
			temp->cooldown = 120;
		}
		temp->nextTower = NULL;
		temp->towerlvl = 1;
		temp->towerType = towerType;
		temp->x = x;
		temp->y = y;
		temp->degrees = 0;
		temp->canShoot = true;
		temp->timer = 0;
		return temp;
	}
	else {
		root->nextTower = newTower(root->nextTower, towerType, x, y);
		return root;
	}
}

Tower* towerDraw(Tower* root, Enemy *target, struct Bullet* bulletRoot) {
	if (root != NULL) {
		root->nextTower = towerDraw(root->nextTower, target, bulletRoot);
		int towerX = 497 + root->x * 99;
		int towerY = 69 + root->y * 99;
		al_draw_rotated_bitmap(root->towerPicture, 50, 50, towerX, towerY, root->degrees * 3.14159 / 180, 0);
		Enemy* finalTarget = getTarget(target, towerX, towerY, root->towerRange);
		if(finalTarget != NULL){
			double goalDegrees = getDegrees(towerX, towerY, finalTarget->x, finalTarget->y);
			root->degrees += degreesChange(root->degrees, goalDegrees);
			if (root->degrees < 0.0) {
				root->degrees += 360.0;
			}
			else if (root->degrees > 360.0) {
				root->degrees -= 360.0;
			}
			if (root->canShoot == true) {
				root->canShoot = false;
				if (root->towerType == 1) {
					if (root->towerlvl == 1) {
						bulletRoot = newBullet(bulletRoot,towerX, towerY, finalTarget, "inne/bullet1(80x80).png", 1);
					}
					else {
						bulletRoot = newBullet(bulletRoot, towerX,towerY, finalTarget, "inne/bullet3(100x100).png", 2);
					}
				}
				else {
					if (root->towerlvl == 1) {
						bulletRoot = newBullet(bulletRoot, towerX, towerY, finalTarget, "inne/bullet2(80x80).png", 3);
					}
					else {
						bulletRoot = newBullet(bulletRoot, towerX, towerY, finalTarget, "inne/bullet4(100x100).png", 4);
					}
				}
			}
		}
		if (root->canShoot == false) {
			root->timer += 1;
			if (root->timer >= root->cooldown) {
				root->canShoot = true;
				root->timer = 0;
			}
		}
		return root;
	}
	else {
		return NULL;
	}
}

double degreesChange(double currentDegrees, double goalDegrees) {
	double rightDegrees = goalDegrees - currentDegrees;
	if (rightDegrees < 0) {
		rightDegrees += 360.0;
	}
	if (rightDegrees <= 180.0) {
		if (rightDegrees >= 10.0) {
			return 10.0;
		}
		else
		{
			return rightDegrees;
		}
	}
	else {
		if (360.0 - rightDegrees >= 10.0) {
			return -10.0;
		}
		else {
			return -(360.0 - rightDegrees);
		}
	}
}

Enemy* getTarget(Enemy* targets, int friendX, int friendY, int distance) {
	if (targets == NULL || targets->x < 0) {
		return NULL;
	}
	else {
		int xDistance = targets->x - friendX;
		int yDistance = targets->y - friendY;
		int totalDistance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
		if (totalDistance <= distance) {
			return targets;
		}
		else {
			return getTarget(targets->nextEnemy, friendX, friendY, distance);
		}
	}
}

Tower* upgradeTower(Tower* root, int x, int y, int *map) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (x == root->x && y == root->y) {
			al_change_directory("../../../resources");
			if (root->towerType == 1) {
				root->towerPicture = al_load_bitmap("inne/tower3(100x100).png");
			}
			else {
				root->towerPicture = al_load_bitmap("inne/tower4(100x100).png");
			}
			root->towerRange += 100;
			root->towerlvl = 2;
			root->cooldown -= 30;
			*(map + x + (10 * y)) -= 2;
			return root;
		}
		else {
			root->nextTower = upgradeTower(root->nextTower, x, y, map);
			return root;
		}
	}
}

Tower* delAllTowers(Tower* root) {
	if (root != NULL) {
		if (root->nextTower != NULL) { root->nextTower = delAllTowers(root->nextTower); }
		free(root);
		return NULL;
	}
	else {
		return NULL;
	}
}
struct Bullet* delAllBullets(struct Bullet* root) {
	if (root != NULL) {
		root->nextBullet = delAllBullets(root->nextBullet);
		free(root);
		return NULL;
	}
	else {
		return NULL;
	}
}

struct Bullet* bulletInit() {
	struct Bullet* temp = (struct Bullet*)malloc(sizeof(struct Bullet));
	temp->active = false;
	return temp;
}