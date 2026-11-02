#ifndef ISLAND_GENERATOR_H
#define ISLAND_GENERATOR_H

#include "shared.h"

typedef enum { TILE_COLOR_GREEN, TILE_COLOR_YELLOW, TILE_COLOR_BLUE } TileColor;

typedef enum { TILE_EMPTY, TILE_STONE, TILE_TREE } ContentType;

typedef struct Tile {
    Vector2 position;
    TileColor color;
    int is_walkable;
    ContentType content;
} Tile_t;

typedef struct Island {
    uint seed;
    uint width;
    uint height;
    uint tile_size;
    uint number_tiles;
    Tile_t *tiles;
} Island_t;

/* island */
Island_t *island_create(uint seed, uint width, uint height, uint tile_size);
void island_render(Island_t *island);
void island_destroy(Island_t *island);

/* tiles */
Tile_t *get_tile(Island_t *island, Vector2 position);
Tile_t *get_tile_with_id(Island_t *island, uint id);
unsigned int get_tile_id(uint island_width, Vector2 position);
int is_walkable(Island_t *island, Vector2 position);
int is_on_map(Island_t *island, Vector2 position);
void get_surroundings(Island_t *island, Vector2 position, uint tile_ids[8]);

#endif /* ISLAND_GENERATOR_H */
