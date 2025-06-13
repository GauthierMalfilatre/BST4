/*
** EPITECH PROJECT, 2025
** RAYv3
** File description:
** Textures for wolf3d
*/
#include "wolf.h"
#include <string.h>

void add_texture(textures_t **head, char *name, int id, char *path)
{
    textures_t *new = malloc(sizeof(textures_t));

    if (!new) {
        return;
    }
    new->name = strdup(name);
    new->texture = sfTexture_createFromFile(path, 0);
    new->image = sfTexture_copyToImage(new->texture);
    new->id = id;
    new->next = *head;
    *head = new;
    return;
}

textures_t *create_textures(void)
{
    textures_t *new = 0;

    return new;
}

textures_t *get_texture(textures_t *textures, char *name)
{
    for (textures_t *temp = textures; temp; temp = temp->next) {
        if (!strcmp(name, temp->name)) {
            return temp;
        }
    }
    return (textures_t *) 0;
}

textures_t *get_texture_from_type(textures_t *textures, int type)
{
    for (textures_t *temp = textures; temp; temp = temp->next) {
        if (type == temp->id) {
            return temp;
        }
    }
    return 0;
}
