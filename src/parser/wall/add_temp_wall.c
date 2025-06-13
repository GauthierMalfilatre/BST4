/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Parse main file for configuration
*/
#include "wolf.h"
#include "parser.h"

int add_temp_wall_p(char **warray, wolf_context_t *context)
{
    int exticode = OK;

    if (!context->maps || !context->n_map) {
        return ERROR;
    }
    maps_t *cmap = context->maps[context->n_map - 1];
    add_temp_wall(&cmap->temp_walls,
        cmap->n_wall, (wall_t){
            .a = (sfVector2f){atof(warray[1]), atof(warray[2])},
            .b = (sfVector2f){atof(warray[3]), atof(warray[4])},
            .type = my_getnbr(warray[5]),
            .is_breakable = 0.f,
            .alpha = 0.5f,
            .builder = (player_t *) 0});
    return exticode;
}
