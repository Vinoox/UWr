TowerDefence: obj/enemy.o obj/game.o obj/levels.o obj/tower.o obj/menu.o obj/TowerDefence.c
	cd obj && gcc enemy.o game.o levels.o tower.o menu.o TowerDefence.o -lm -o ../TowerDefnece

obj/enemy.o: ../TowerDefence/enemy.h ../TowerDefence/enemy.c
	cd ../TowerDefence/ && gcc -c enemy.c -o ../Build/obj/enemy.o

obj/game.o: ../TowerDefence/game.h ../TowerDefence/game.c
	cd ../TowerDefence/ && gcc -c game.c -o ../Build/obj/game.o

obj/levels.o: ../TowerDefence/sceneEasyLevel.c ../TowerDefence/sceneMediumLevel.c ../TowerDefence/sceneHardLevel.c ../TowerDefence/sceneLevel.h
	cd ../TowerDefence/ && gcc -c sceneEasyLevel.c sceneMediumLevel.c sceneHardLevel.c -o ../Build/obj/level.o

obj/tower.o: ../TowerDefence/tower.c ../TowerDefence/tower.h
	cd ../TowerDefence/ && gcc -c tower.c -o ../Build/obj/tower.o

obj/menu.o: ../TowerDefence/sceneMenu.c ../TowerDefence/sceneHelp.c ../TowerDefence/sceneMenu.h 
	cd ../TowerDefence/ && gcc -c sceneMenu.c sceneHelp.c -o ../Build/obj/menu.o

obj/TowerDefence.o: ../TowerDefence/TowerDefence.c
	cd ../TowerDefence/ && gcc -c TowerDefence.c -o ../Build/obj/towerDefenc.o