#include "island_generator.h"

#include <stdlib.h> /* malloc(), NULL, free() */

#include "shared.h"

#define MAX_GRASS_TILES 512

static void island_generate(Island_t *island);

Island_t *island_create(unsigned int seed, unsigned int width,
                        unsigned int height, unsigned int tile_size) {
  /* allocate memory for the island */
  Island_t *island = (Island_t *)malloc(sizeof(Island_t));
  if (!island)
    return NULL;

  /* allocate memory for the island tiles */
  island->tile_size = tile_size;
  island->width = width / tile_size;
  island->height = height / tile_size;
  island->number_tiles = island->width * island->height;
  island->tiles = (Tile_t *)malloc(sizeof(Tile_t) * island->number_tiles);
  if (!island->tiles)
    return NULL;

  /* set seed */
  island->seed = seed;
  SetRandomSeed(seed);

  /* generate island */
  island_generate(island);

  return island;
}

static void island_generate(Island_t *island) {
  /* make all tiles first water */
  for (unsigned int i = 0; i < island->number_tiles; i++) {
    island->tiles[i].color = TILE_COLOR_BLUE;
    island->tiles[i].position.x = i % island->width;
    island->tiles[i].position.y = i / island->width;
  }

  /* start building the island */
  unsigned int grass_tiles_counter = 0;
  unsigned int grass_tiles[MAX_GRASS_TILES];

  /* set the first grass tile in the center */
  Vec2_t center = {island->width / 2, island->height / 2};
  island->player_starting_position = (Vec2_t){center.x, center.y};
  get_tile(island, (Vec2_t){center.x, center.y})->color = TILE_COLOR_GREEN;
  grass_tiles[grass_tiles_counter] =
      get_tile_id(island->width, (Vec2_t){center.x, center.y});
  grass_tiles_counter++;

  /* create the island itself */
  while (grass_tiles_counter < MAX_GRASS_TILES) {
    unsigned int random_tile_id =
        grass_tiles[GetRandomValue(0, grass_tiles_counter - 1)];

    Tile_t *tile = &island->tiles[random_tile_id];

    unsigned int x = tile->position.x;
    unsigned int y = tile->position.y;

    unsigned int direction = GetRandomValue(0, 3);

    Vec2_t new_position = {x, y};

    switch (direction) {
    case 0: // up
      if (y == 0)
        continue;
      new_position.y--;
      break;

    case 1: // right
      if (x + 1 >= island->width)
        continue;
      new_position.x++;
      break;

    case 2: // down
      if (y + 1 >= island->height)
        continue;
      new_position.y++;
      break;

    case 3: // left
      if (x == 0)
        continue;
      new_position.x--;
      break;
    }

    Tile_t *new_tile = get_tile(island, new_position);

    // Don't add an already-grass tile
    if (new_tile->color == TILE_COLOR_GREEN)
      continue;

    new_tile->color = TILE_COLOR_GREEN;

    grass_tiles[grass_tiles_counter] = get_tile_id(island->width, new_position);

    grass_tiles_counter++;
  }

  /* create sand surroundings */
  unsigned int tile_ids[8] = {0};
  for (int y = 0; y < island->height; y++) {
    for (int x = 0; x < island->width; x++) {
      Vec2_t pos = (Vec2_t){x, y};
      if (is_walkable(island, pos)) {
        get_surroundings(island, pos, tile_ids);
        for (int i = 0; i < 8; i++) {
          if (tile_ids[i] == 0)
            continue;
          if (island->tiles[tile_ids[i]].color == TILE_COLOR_BLUE) {
            get_tile(island, pos)->color = TILE_COLOR_YELLOW;
          }
        }
      }
    }
  }
}

void island_render(Island_t *island) {
  for (unsigned int y = 0; y < island->height; y++) {
    for (unsigned int x = 0; x < island->width; x++) {
      Tile_t *tile = get_tile(island, (Vec2_t){x, y});
      Color tile_color;
      switch (tile->color) {
      case TILE_COLOR_GREEN:
        tile_color = (Color){122, 191, 36, 255};
        break;
      case TILE_COLOR_YELLOW:
        tile_color = (Color){245, 206, 51, 255};
        break;
      case TILE_COLOR_BLUE:
        tile_color = (Color){37, 150, 190, 255};
        break;
      }
      DrawRectangle(tile->position.x * island->tile_size,
                    tile->position.y * island->tile_size, island->tile_size,
                    island->tile_size, tile_color);
    }
  }
}
void island_destroy(Island_t *island) { free(island); }

/* tiles */
Tile_t *get_tile(Island_t *island, Vec2_t position) {
  return &island->tiles[position.y * island->width + position.x];
}

unsigned int get_tile_id(unsigned int island_width, Vec2_t position) {
  return position.y * island_width + position.x;
}

int is_walkable(Island_t *island, Vec2_t position) {
  if (get_tile(island, position)->color == TILE_COLOR_BLUE) {
    return 0;
  }
  return 1;
}

int is_on_map(Island_t *island, Vec2_t position) {
  if (position.x < 0 || position.x > island->width || position.y < 0 ||
      position.y > island->height) {
    return 0;
  }
  return 1;
}

void get_surroundings(Island_t *island, Vec2_t position,
                      unsigned int tile_ids[8]) {
  int i = 0;
  for (int y = -1; y < 2; y++) {
    for (int x = -1; x < 2; x++) {
      Vec2_t pos = (Vec2_t){position.x + x, position.y + y};
      if (is_on_map(island, (Vec2_t){pos.x, pos.y})) {
        tile_ids[i] = get_tile_id(island->width, pos);
        i++;
      }
    }
  }
}
