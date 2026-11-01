#ifndef TEXTURES_H
#define TEXTURES_H

#include "shared.h"

typedef struct TextureData {
        char *name;
        Texture2D texture;
} TextureData_t;

typedef struct TextureMgr {
        TextureData_t *textures;
        int textures_count;
} TextureMgr_t;

TextureMgr_t *tm_init();
void tm_add(TextureMgr_t *tm, const char *name);
Texture2D get_texture(TextureMgr_t *tm, const char *name);
void tm_destroy(TextureMgr_t *tm);

#endif /* TEXTURES_H */
