#include "player.h"

#include <stdlib.h>

Player_t *player_create(Island_t *island, unsigned int size)
{
        Player_t *player = (Player_t *)malloc(sizeof(Player_t));
        if (!player) return NULL;
        player->position = (Vector2){30, 30};
        player->size = size;

        return player;
}

void player_render(Player_t *player)
{
        DrawRectangle(player->position.x * player->size,
                      player->position.y * player->size, player->size,
                      player->size, (Color){255, 230, 200, 255});
}

void player_input(Player_t *player, Island_t *island, Vector2 mouse_pos)
{
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                if (is_walkable(island,
                                (Vector2){mouse_pos.x / player->size,
                                          mouse_pos.y / player->size})) {
                        player->position.x = mouse_pos.x / player->size;
                        player->position.y = mouse_pos.y / player->size;
                }
        }
}

void player_destroy(Player_t *player) { free(player); }
