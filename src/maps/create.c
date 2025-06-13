/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

maps_t *create_map(char *name)
{
    maps_t *new = malloc(sizeof(maps_t));

    new->bullets = (bullet_t *) 0;
    new->n_wall = 0;
    new->walls = NULL;
    new->bsp = (bsp_t *) 0;
    new->stuffs = (stuffs_t *) 0;
    new->spawns = (spawns_t *) 0;
    new->heals = (heals_t *) 0;
    new->name = strdup(name);
    new->temp_walls = (temp_wall_t *) 0;
    return new;
}
