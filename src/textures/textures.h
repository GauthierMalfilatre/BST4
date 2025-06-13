/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Linked list of textures.
*/
#ifndef TEXTURES_WOLF_3D_H
    #define TEXTURES_WOLF_3D_H
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>

/* Textures struct */
typedef struct textures_s {
    char *name;
    int id;
    sfTexture *texture;
    sfImage *image;
    struct textures_s *next;
} textures_t;

void add_texture(textures_t **head, char *name, int id, char *path);

textures_t *get_texture(textures_t *textures, char *name);
textures_t *get_texture_from_type(textures_t *textures, int type);

void destroy_textures(textures_t *textures);

#endif /* TEXTURES_WOLF_3D_H */
