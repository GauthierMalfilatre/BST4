/*
** EPITECH PROJECT, 2025
** RAYv3
** File description:
** Destroy textures for ray v3
*/
#include "wolf.h"

static void del_texture(textures_t *texture)
{
    free(texture->name);
    sfTexture_destroy(texture->texture);
    sfImage_destroy(texture->image);
    free(texture);
    return;
}

void destroy_textures(textures_t *textures)
{
    if (!textures) {
        return;
    }
    if (textures->next) {
        destroy_textures(textures->next);
    }
    del_texture(textures);
    return;
}
