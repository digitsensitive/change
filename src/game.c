#include "game.h"

#include "island_generator.h"
#include "player.h"

#define ZOOM_FACTOR 4

const unsigned int TILE_SIZE = 16;
const char *GAME_TITLE = "Change";
const unsigned int GAME_FPS = 60;

void game_init(Game_t *game) {
  InitWindow(game->width, game->height, game->title);
  SetTargetFPS(GAME_FPS);

  /* create island */
  game->island =
      island_create(game->seed, game->width, game->height, TILE_SIZE);

  /* create player */
  game->player = player_create(game->island, TILE_SIZE);

  /* set weather */
  // game->weather = init_weather();

  /* debug */
  game->debug.is_enabled = 1;
  game->debug.running_time = 0;

  /* mouse */
  game->mouse_pos = GetMousePosition();
}

void game_loop(Game_t *game) {
  while (!WindowShouldClose()) {
    game_update(game);
    game_render(game);
  }
}

void game_update(Game_t *game) {
  /* update running time */
  if (game->debug.is_enabled) {
    game->debug.running_time++;
  }

  /* update mouse position */
  game->mouse_pos = GetMousePosition();

  switch (game->scene) {
  case SCENE_MENU:
    /* menu scene */
    break;
  case SCENE_GAMEPLAY:
    /* gameplay scene */
    player_input(game->player, game->island, game->mouse_pos);
    // weather_update(game->weather);
    break;
  case SCENE_GAME_OVER:
    /* menu scene */
    break;
  }
}

void game_render(Game_t *game) {
  BeginDrawing();
  switch (game->scene) {
  case SCENE_MENU:
    /* menu scene */
    break;
  case SCENE_GAMEPLAY:
    /* gameplay scene */
    island_render(game->island);
    player_render(game->player);
    // weather_render(game->weather);
    DrawText(TextFormat("Seed: %i", game->island->seed), 200, 80, 20, WHITE);
    if (game->debug.is_enabled) {
      DrawText(TextFormat("FPS: %i", GetFPS()), 200, 100, 20, WHITE);
      DrawText(
          TextFormat("Time running (sec): %i", game->debug.running_time / 60),
          200, 120, 20, WHITE);
    }

    break;
  case SCENE_GAME_OVER:
    /* menu scene */
    break;
  }

  /* draw own cursor */
  DrawCircle(game->mouse_pos.x, game->mouse_pos.y, 5.0f, WHITE);
  DrawCircleLinesV(game->mouse_pos, 8.0f, BLACK);

  EndDrawing();
}

void game_destroy(Game_t *game) {
  island_destroy(game->island);
  player_destroy(game->player);
  // weather_destroy(game->weather);
  CloseWindow();
}
