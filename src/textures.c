#include "textures.h"

#include <stdlib.h>
#include <string.h>

const int MAX_TEXTURES = 20;

TextureMgr_t *tm_init()
{
    TextureMgr_t *tm = (TextureMgr_t *)malloc(sizeof(TextureMgr_t));
    if (!tm) return NULL;

    tm->textures =
        (TextureData_t *)malloc(sizeof(TextureData_t) * MAX_TEXTURES);
    if (!tm->textures) return NULL;

    tm->textures_count = 0;

    return tm;
}

void tm_add(TextureMgr_t *tm, const char *name)
{
    if (tm->textures_count < MAX_TEXTURES) {
        tm->textures[tm->textures_count].name = malloc(strlen(name) + 1);
        strcpy(tm->textures[tm->textures_count].name, name);
        tm->textures[tm->textures_count].texture = LoadTexture(name);
        tm->textures_count++;
    } else {
        /* no more capacity for textures */
    }
}

Texture2D get_texture(TextureMgr_t *tm, const char *name)
{
    for (int i = 0; i < tm->textures_count; i++) {
        if (strcmp(name, tm->textures[i].name) == NULL) {
            return tm->textures[i].texture;
        }
    }
    return (Texture2D){};
}

void tm_destroy(TextureMgr_t *tm)
{
    for (int i = 0; i < tm->textures_count; i++) {
        free(tm->textures[i].name);
    }

    free(tm->textures);
    free(tm);
}
