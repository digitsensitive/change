#ifndef PLAYER_H
#define PLAYER_H

#include "island_generator.h"
#include "shared.h"

typedef struct Player {
    Vec2_t position;
    unsigned int size;
} Player_t;

Player_t* player_create(Island_t *island, unsigned int size);
void player_render(Player_t *player);
void player_input(Player_t *player, Island_t *island, Vector2 mouse_pos);
void player_destroy(Player_t *player);

#endif /* PLAYER_H */
