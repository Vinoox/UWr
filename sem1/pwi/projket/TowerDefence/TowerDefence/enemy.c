#include "enemy.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdbool.h>

extern int gameMoney;
extern int gameLife;

Point * createPoint(int a, int b) {
	Point* temp = (Point*)malloc(sizeof(Point));
	temp->x = a;
	temp->y = b;
	temp->nextPoint = NULL;
	return temp;
}

Point* newPoint(Point* rootPoint, int a, int b) {
	if (rootPoint == NULL) {
		rootPoint = createPoint(a, b);
		return rootPoint;
	}
	else {
		rootPoint->nextPoint = newPoint(rootPoint->nextPoint, a, b);
	}
	return rootPoint;
}

Point* getPoints(char* path) {
	Point* start = NULL;

	FILE* f = fopen(path, "r");
	if (!f) gameCrashLog("blad otwarcia pliku %s", path);

	int x, y;

	while (fscanf(f, "%d %d", &x, &y) == 2) {
		start = newPoint(start, x, y);
	}

	fclose(f);

	return start;
}

Enemy* createEnemy(char* path, Point* start, int hp) {
	Enemy* temp = (Enemy*)calloc(1, sizeof(Enemy));
	al_change_directory("../../../resources");
	temp->enemyPicture = al_load_bitmap(path);
	temp->x = 600;
	temp->y = 965;
	temp->hp = hp;
	temp->damage = 50;
	temp->nextEnemy = NULL;
	temp->point = start;
	temp->degrees = 90.0;
	temp->height = al_get_bitmap_height(temp->enemyPicture);
	temp->width = al_get_bitmap_width(temp->enemyPicture);
	temp->active = true;
	return temp;
}

Enemy* newEnemy(Enemy* rootEnemy, char* path, Point* start, int hp) {
	if (rootEnemy == NULL) {
		rootEnemy = createEnemy(path, start, hp);
		return rootEnemy;
	}
	else {
		rootEnemy->nextEnemy = newEnemy(rootEnemy->nextEnemy, path, start, hp);
		return rootEnemy;
	}
}

Enemy* enemyDraw(Enemy* rootEnemy) {
	if (rootEnemy != NULL) {
		static angle = 0;
		int xDistance = abs(rootEnemy->point->x - rootEnemy->x);
		int yDistance = abs(rootEnemy->point->y - rootEnemy->y);
		int totalDistance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
		if (totalDistance < 5) {
			if (rootEnemy->point->nextPoint == NULL) {
				gameLife -= rootEnemy->damage;
				rootEnemy = deleteEnemy(rootEnemy);
				rootEnemy = enemyDraw(rootEnemy);
			}
			else rootEnemy->point = rootEnemy->point->nextPoint;
		}
		else {
			al_draw_rotated_bitmap(rootEnemy->enemyPicture, rootEnemy->width / 2, rootEnemy->height / 2, rootEnemy->x, rootEnemy->y, rootEnemy->degrees * 3.14159 / 180, 0);
			int speed = 2;
			if (rootEnemy->x != rootEnemy->point->x) {
				if (rootEnemy->x > rootEnemy->point->x) {
					rootEnemy->x -= speed;
					angle = 270;
				}
				else {
					rootEnemy->x += speed;
					angle = 90;
				}
			}

			else {
				if (rootEnemy->y > rootEnemy->point->y) {
					rootEnemy->y -= speed;
					angle = 0;
				}
				else {
					rootEnemy->y += speed;
					angle = 180;
				}
			}
			rootEnemy->degrees = angle;
			rootEnemy->nextEnemy = enemyDraw(rootEnemy->nextEnemy);
		}
	}
	return checkHp(rootEnemy);
}

Enemy* checkHp(Enemy* rootEnemy) {
	if (rootEnemy != NULL) {
		if (rootEnemy->hp <= 0) {
			gameMoney += 25;
			rootEnemy = deleteEnemy(rootEnemy);
			rootEnemy = checkHp(rootEnemy);
		}
		else {
			rootEnemy->nextEnemy = checkHp(rootEnemy->nextEnemy);
		}
	}
	return rootEnemy;
}

Enemy* deleteEnemy(Enemy* rootEnemy) {
	if (rootEnemy->nextEnemy == NULL) {
		free(rootEnemy);
		return NULL;
	}
	else {
		Enemy* temp = rootEnemy->nextEnemy;
		free(rootEnemy);
		return temp;
	}
}

Enemy* delAllEnemies(Enemy* root) {
	if (root != NULL) {
		root->nextEnemy = delAllEnemies(root->nextEnemy);
		free(root);
		return NULL;
	}
	else {
		return NULL;
	}
}