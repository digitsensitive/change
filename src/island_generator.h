#ifndef ISLAND_GENERATOR_H
#define ISLAND_GENERATOR_H

#include "shared.h"

typedef enum  {
    TILE_COLOR_GREEN,
    TILE_COLOR_YELLOW,
    TILE_COLOR_BLUE
} TileColor;

typedef struct Tile {
    Vec2_t position;
    TileColor color;
    int is_walkable;
} Tile_t;

typedef struct Island {
    unsigned int seed;
    unsigned int width;
    unsigned int height;
    unsigned int tile_size;
    unsigned int number_tiles;
    Vec2_t player_starting_position;
    Tile_t *tiles;
} Island_t;

/* island */
Island_t *island_create(unsigned int seed, unsigned int width, unsigned int height,unsigned int tile_size);
void island_render(Island_t *island);
void island_destroy(Island_t *island);

/* tiles */
Tile_t *get_tile(Island_t *island, Vec2_t position);
unsigned int get_tile_id(unsigned int island_width, Vec2_t position);
int is_walkable(Island_t *island, Vec2_t position);
int is_on_map(Island_t *island, Vec2_t position);
void get_surroundings(Island_t *island, Vec2_t position,
                      unsigned int tile_ids[8]);

#endif /* ISLAND_GENERATOR_H */
