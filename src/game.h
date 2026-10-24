#ifndef GAME_H
#define GAME_H

/* includes */
#include "../include/raylib.h"
#include "island_generator.h"
#include "player.h"

/* const variables */
#define MAX_TITLE_LENGTH 256

/* variables */
typedef enum  {
    SCENE_MENU,
    SCENE_GAMEPLAY,
    SCENE_GAME_OVER
} SceneType;

typedef struct Debug {
	int is_enabled;
	int running_time;
} Debug_t;

typedef struct Game {
    unsigned int width;
    unsigned int height;
    unsigned int seed;
    char title[MAX_TITLE_LENGTH];
    SceneType scene;
    Island_t *island;
    Player_t *player;
		Vector2 mouse_pos;
		Debug_t debug;
} Game_t;

/* functions */
void game_init(Game_t *game);
void game_loop(Game_t *game);
void game_update(Game_t *game);
void game_render(Game_t *game);
void game_destroy(Game_t *game);

#endif /* GAME_H */
