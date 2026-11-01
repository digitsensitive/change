#include "island_generator.h"

#include <stdlib.h> /* malloc(), NULL, free() */

#include "shared.h"

#define MAX_GRASS_TILES 512

static void island_generate(Island_t *island);

Island_t *island_create(uint seed, uint width, uint height, uint tile_size)
{
        /* allocate memory for the island */
        Island_t *island = (Island_t *)malloc(sizeof(Island_t));
        if (!island) return NULL;

        /* allocate memory for the island tiles */
        island->tile_size = tile_size;
        island->width = width / tile_size;
        island->height = height / tile_size;
        island->number_tiles = island->width * island->height;
        island->tiles = (Tile_t *)malloc(sizeof(Tile_t) * island->number_tiles);
        if (!island->tiles) return NULL;

        /* set seed */
        island->seed = seed;
        SetRandomSeed(seed);

        /* generate island */
        island_generate(island);

        return island;
}

static void island_generate(Island_t *island)
{
        /* make all tiles first water */
        for (uint i = 0; i < island->number_tiles; i++) {
                island->tiles[i].color = TILE_COLOR_BLUE;
                island->tiles[i].position.x = i % island->width;
                island->tiles[i].position.y = i / island->width;
                island->tiles[i].is_walkable = 0;
        }

        /* start building the island */
        uint grass_tiles_counter = 0;
        uint grass_tiles[MAX_GRASS_TILES];

        /* set the first grass tile in the center */
        Vector2 center = {island->width / 2, island->height / 2};
        get_tile(island, (Vector2){center.x, center.y})->color =
            TILE_COLOR_GREEN;
        grass_tiles[grass_tiles_counter] =
            get_tile_id(island->width, (Vector2){center.x, center.y});
        grass_tiles_counter++;

        /* create the island itself */
        while (grass_tiles_counter < MAX_GRASS_TILES) {
                unsigned int random_tile_id =
                    grass_tiles[GetRandomValue(0, grass_tiles_counter - 1)];

                Tile_t *tile = &island->tiles[random_tile_id];

                int x = tile->position.x;
                int y = tile->position.y;

                uint direction = GetRandomValue(0, 3);

                Vector2 new_position = {x, y};

                switch (direction) {
                        case 0:  // up
                                if (y == 0) continue;
                                new_position.y--;
                                break;

                        case 1:  // right
                                if (x + 1 >= island->width) continue;
                                new_position.x++;
                                break;

                        case 2:  // down
                                if (y + 1 >= island->height) continue;
                                new_position.y++;
                                break;

                        case 3:  // left
                                if (x == 0) continue;
                                new_position.x--;
                                break;
                }

                Tile_t *new_tile = get_tile(island, new_position);

                // Don't add an already-grass tile
                if (new_tile->color == TILE_COLOR_GREEN) continue;

                new_tile->color = TILE_COLOR_GREEN;
                new_tile->is_walkable = 1;
                grass_tiles[grass_tiles_counter] =
                    get_tile_id(island->width, new_position);

                grass_tiles_counter++;
        }

        /* create sand surroundings */
        uint tile_ids[8] = {0};
        for (uint y = 0; y < island->height; y++) {
                for (uint x = 0; x < island->width; x++) {
                        Vector2 pos = (Vector2){x, y};
                        if (is_walkable(island, pos)) {
                                get_surroundings(island, pos, tile_ids);
                                for (int i = 0; i < 8; i++) {
                                        if (tile_ids[i] == 0) continue;
                                        if (island->tiles[tile_ids[i]].color ==
                                            TILE_COLOR_BLUE) {
                                                get_tile(island, pos)->color =
                                                    TILE_COLOR_YELLOW;
                                        }
                                }
                        }
                }
        }
}

void island_render(Island_t *island)
{
        for (uint y = 0; y < island->height; y++) {
                for (uint x = 0; x < island->width; x++) {
                        Tile_t *tile = get_tile(island, (Vector2){x, y});
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
                                      tile->position.y * island->tile_size,
                                      island->tile_size, island->tile_size,
                                      tile_color);
                }
        }
}
void island_destroy(Island_t *island) { free(island); }

/* tiles */
Tile_t *get_tile(Island_t *island, Vector2 position)
{
        return &island
                    ->tiles[(int)position.y * island->width + (int)position.x];
}

unsigned int get_tile_id(uint island_width, Vector2 position)
{
        return position.y * island_width + position.x;
}

int is_walkable(Island_t *island, Vector2 position)
{
        if (get_tile(island, position)->is_walkable) {
                return 1;
        }
        return 0;
}

int is_on_map(Island_t *island, Vector2 position)
{
        if (position.x < 0 || position.x > island->width || position.y < 0 ||
            position.y > island->height) {
                return 0;
        }
        return 1;
}

void get_surroundings(Island_t *island, Vector2 position, uint tile_ids[8])
{
        int i = 0;
        for (int y = -1; y < 2; y++) {
                for (int x = -1; x < 2; x++) {
                        Vector2 pos = (Vector2){position.x + x, position.y + y};
                        if (is_on_map(island, (Vector2){pos.x, pos.y})) {
                                tile_ids[i] = get_tile_id(island->width, pos);
                                i++;
                        }
                }
        }
}
