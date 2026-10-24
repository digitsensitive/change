/* my entry for the olc jam 2026; topic: change */
/* each char was written by hand */

/* includes */
#include <stddef.h>
#include <time.h>

#include "game.h"

/* main entry point */
int main(void)
{
        SetRandomSeed((unsigned int)time(NULL));
        Game_t game = {2560,     1440,           GetRandomValue(10, 9999999),
                       "Change", SCENE_GAMEPLAY, NULL};

        game_init(&game);
        game_loop(&game);
        game_destroy(&game);

        return 0;
}
