/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

static void destroy_map(maps_t *map)
{
    destroy_bullets(map->bullets);
    delete_spawns(map->spawns);
    delete_bsp(map->bsp);
    destroy_stuffs(map->stuffs);
    free(map->walls);
    free(map->name);
    free(map);
}

void destroy_maps(maps_t **maps, const int nmap)
{
    if (!maps) {
        return;
    }
    for (int i = 0; i < nmap && maps[i]; i++) {
        destroy_map(maps[i]);
    }
    free(maps);
}
