#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sceneLevel.h"
#include "sceneMenu.h"
#include "tower.h"

const int FPS = 60;
const int SCREEN_W = 1920;
const int SCREEN_H = 1030;
Scene activeScene;
static bool keyState[ALLEGRO_KEY_MAX];
//static bool *mouseState = NULL;
int mouseX, mouseY;
//struct Bullet* rootBullet = NULL;
//enemy* badGuy = NULL;
//toolbar* toolbarRoot = NULL;
//tower* towerRoot = NULL;
static ALLEGRO_DISPLAY* gameDisplay;
static ALLEGRO_EVENT_QUEUE* gameEventQueue;
static ALLEGRO_TIMER* gameTimer;
ALLEGRO_FONT* font;
int gameMoney;
int gameLife;
//extern Enemy* badGuy;


const char* gameTitle = "PWI Tower Defence";


void allegroStart(void);

void gameMainLoop(void);

void gameLogicUpdate(void);

void gameDraw(void);

void gameDestroy(void);


void allegroStart(void)
{
	if (!al_init()) {
		gameCrashLog("blad inicjalizacji allegro");
	}
	gameLog("allegro zainicjalizowane");

	al_change_directory("../resources");
	gameLog("%s", al_get_current_directory());

	if (!al_init_image_addon()) {
		gameCrashLog("blad inicjalizacji dodatku image");
	}
	gameLog("allegro/image zainicjalizowane");

	if (!al_init_native_dialog_addon()) {
		gameCrashLog("blad inicjalizacji dodatku dialog");
	}
	gameLog("allegro/dialog zainicjalizowane");	
	
	if (!al_init_font_addon()) {
		gameCrashLog("blad inicjalizacji dodatku font");
	}
	gameLog("allegro/font zainicjalizowane");	
	
	if (!al_init_primitives_addon()) {
		gameCrashLog("blad inicjalizacji dodatku primitives");
	}
	gameLog("allegro/primitives zainicjalizowane");

	if (!al_init_ttf_addon()) {
		gameCrashLog("blad inicjalizacji dodatku ttf");
	}
	gameLog("allegro/ttf zainicjalizowane");
	
	font = al_load_font("cascaydia.otf", 40, 0);
	if (!font) {
		gameCrashLog("blad inicjalizacji czcionki");
	}
	gameLog("allegro/czcionka zainicjalizowana");

	gameDisplay = al_create_display(SCREEN_W, SCREEN_H);
	if (!gameDisplay) {
		gameCrashLog("blad inicjalizacji allegro display");
	}
	gameLog("allegro/display zainicjalizowane");

	gameTimer = al_create_timer(1.0 / FPS);
	if (!gameTimer){
		gameCrashLog("blad inicjalizacji allegro timer");
	}
	gameLog("allegro/timer zainicjalizowane");

	gameEventQueue = al_create_event_queue();
	if (!gameEventQueue) {
		gameCrashLog("blad inicjalizacji allegro queue");
	}
	gameLog("allegro/queue zainicjalizowane");

	if (!al_install_keyboard()) {
		gameCrashLog("blad inicjalizacji klawiatury");
	}
	gameLog("klawiatura zainicjalizowana");

	if (!al_install_mouse()) {
		gameCrashLog("blad inicjalizacji myszki");
	}
	gameLog("myszka zainicjalizowana");

	gameLog("kalwiatura ma %d przyciskow", ALLEGRO_KEY_MAX);

	// eventy
	al_register_event_source(gameEventQueue, al_get_display_event_source(gameDisplay));
	al_register_event_source(gameEventQueue, al_get_timer_event_source(gameTimer));
	al_register_event_source(gameEventQueue, al_get_keyboard_event_source());
	al_register_event_source(gameEventQueue, al_get_mouse_event_source());

	// start timera
	al_start_timer(gameTimer);
}

void gameMainLoop(void)
{
	bool running = true;
	ALLEGRO_EVENT event;
	int nextFrame = 0;
	while (running) {
		al_wait_for_event(gameEventQueue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			gameLog("X klikniety, zamykanie petli");
			running = false;
			break;

		case ALLEGRO_EVENT_TIMER:
			if (event.timer.source == gameTimer)
			{
				nextFrame++;
			}
			break;


		case ALLEGRO_EVENT_KEY_DOWN:
			gameLog("klawisz %d wcisniety", event.keyboard.keycode);
			keyState[event.keyboard.keycode] = true;
			if (activeScene.onKeyDown)
			{
				(*activeScene.onKeyDown)(event.keyboard.keycode);
			}
			
			break;

		case ALLEGRO_EVENT_KEY_UP:
			gameLog("klawisz %d wycisniety", event.keyboard.keycode);
			keyState[event.keyboard.keycode] = false;
			if (activeScene.onKeyUp)
			{
				(*activeScene.onKeyUp)(event.keyboard.keycode);
			}
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			gameLog("klawisz myszki %d wcisniety w %d %d", event.mouse.button, event.mouse.x, event.mouse.y);
			//mouseState[event.mouse.button] = true;
			//mouseClickToolbar(toolbarRoot, event.mouse.x, event.mouse.y);
			//switch (toolbarRoot->status) {
			//case 1:
			//	towerRoot = towerFunction(map, 1, event.mouse.x, event.mouse.y, towerRoot, 1);
			//	break;
			//case 2:
			//	towerRoot = towerFunction(map, 2, event.mouse.x, event.mouse.y, towerRoot, 1);
			//	break;
			//case 3:
			//	towerRoot = towerFunction(map, 1, event.mouse.x, event.mouse.y, towerRoot, 2);
			//	break;
			//case 4:
			//	towerRoot = towerFunction(map, 1, event.mouse.x, event.mouse.y, towerRoot, 3);
			//	break;
			//}
			if (activeScene.onMouseDown)
			{
				(*activeScene.onMouseDown)(event.mouse.button, event.mouse.x, event.mouse.y, 0);
			}
			if (activeScene.name[0] == 'M') {
				running = activeScene.quit();
			}
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			gameLog("klawisz myszki %d wycisniety w %d %d", event.mouse.button, event.mouse.x, event.mouse.y);
			//mouseState[event.mouse.button] = false;
			if (activeScene.onMouseUp)
			{
				(*activeScene.onMouseUp)(event.mouse.button, event.mouse.x, event.mouse.y, 0);
			}
			break;


		case ALLEGRO_EVENT_MOUSE_AXES:
			gameLog("myszka ruszona do %d %d", event.mouse.x, event.mouse.y);
			mouseX = event.mouse.x;
			mouseY = event.mouse.y;
			//badGuy->x = event.mouse.x;
			//badGuy->y = event.mouse.y;
			if (activeScene.onMouseMove) 
			{
				(*activeScene.onMouseMove)(0, event.mouse.x, event.mouse.y, 0);
			}
			break;


		default:
			break;
		}

		if (nextFrame > 0 && al_is_event_queue_empty(gameEventQueue))
		{
			gameLogicUpdate();
			gameDraw();
			nextFrame = 0;
		}
	}


}

void gameLogicUpdate(void)
{
	if (activeScene.update)
	{
		(*activeScene.update)();
	}
}

void gameDraw(void)
{
	if (activeScene.draw)
	{
		(*activeScene.draw)();
	}
	//rootBullet = bulletDraw(rootBullet);
	//toolbarDraw(toolbarRoot);
	//towerRoot = towerDraw(towerRoot, badGuy);
	al_flip_display();
}

void gameDestroy(void)
{
	//globalFree();
	al_shutdown_image_addon();
	al_shutdown_native_dialog_addon();
	al_destroy_font(font);
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_destroy_timer(gameTimer);
	al_destroy_event_queue(gameEventQueue);
	al_destroy_display(gameDisplay);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	//free(mouseState);
}

void gameStart(void)
{
	//getMap(map);
	gameLog("uruchamianie allegro");
	allegroStart();
	gameLog("allegro dziala\nuruchamianie zmiennych");
	//globalInit();
	gameSceneChange(sceneMenuCreate());
	//toolbarRoot = toolbarInit();
	gameLog("zmienne dzialaja\nuruchamianie rysowania");
	gameDraw();
	gameLog("rysowanie dziala\nuruchamiane petli i rozpoczynanie rozgrywki");
	gameMainLoop();
	gameLog("koniec gry\nzamykanie programu");
	gameDestroy();
}

void gameSceneChange(Scene nextScene)
{
	gameLog("zmiana sceny z %s na %s", activeScene.name, nextScene.name);
	if (activeScene.destroy)
	{
		(*activeScene.destroy)();
	}
	activeScene = nextScene;
	if (activeScene.initialize)
	{
		(*activeScene.initialize)();
	}
}

bool buttonPresed(Button btn, MousePos mouse) {
	if (mouse.x >= btn.x && mouse.x <= btn.x + btn.w && mouse.y <= btn.y + btn.h && mouse.y >= btn.y) {
		return true;
	}
	return false;
}

void gameCrashLog(const char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	gameWriteLog(format, arg, 1);
	va_end(arg);
	fprintf(stderr, "error, zatrzymywanie");
	al_rest(2);
	exit(1);
}

void gameLog(const char* format, ...)
{
	if (LOG_ENABLED) {
		va_list arg;
		va_start(arg, format);
		gameWriteLog(format, arg, 0);
		va_end(arg);
	}
}

void gameWriteLog(const char* format, va_list arg, int type) 
{
	if (LOG_ENABLED) {
		static bool clean = true;
		FILE* plik = NULL;
		plik = fopen("log.txt", clean ? "w" : "a");
		if (plik) {
			va_list arg2;
			va_copy(arg2, arg);
			vfprintf(plik, format, arg2);
			fflush(plik);
			va_end(arg2);
			fprintf(plik, "\n");
			fclose(plik);
		}
		va_list arg3;
		va_copy(arg3, arg);
		char* message = malloc(256 * sizeof(bool));
		if (message && type == 1)
		{
			vsprintf(message, format, arg3);
			al_show_native_message_box(NULL, "ERROR", "ERROR", message, 0, 0);
			free(message);
		}
		vfprintf(stderr, format, arg);
		fprintf(stderr, "\n");
		clean = false;
	}
}