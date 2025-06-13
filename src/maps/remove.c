/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"

void remove_wall_at_index(wall_t **walls, int *count, int index)
{
    int new_count = *count - 1;

    if (!walls || !*walls || !count || index < 0 || index >= *count)
        return;
    if (index < new_count) {
        memmove(&(*walls)[index], &(*walls)[index + 1],
            sizeof(wall_t) * (new_count - index));
    }
    *walls = realloc(*walls, sizeof(wall_t) * new_count);
    *count = new_count;
}

void remove_wall(wall_t **walls, int *count, int index, int dmg)
{
    int new_count = *count - 1;

    if (!walls || !*walls || !count || index < 0 || index >= *count)
        return;
    if ((*walls)[index].is_breakable == 0.f) {
        return;
    } else {
        (*walls)[index].is_breakable -= dmg;
        if ((*walls)[index].is_breakable > 0.f) {
            return;
        }
    }
    if (index < new_count) {
        memmove(&(*walls)[index], &(*walls)[index + 1],
            sizeof(wall_t) * (new_count - index));
    }
    *walls = realloc(*walls, sizeof(wall_t) * new_count);
    *count = new_count;
}
