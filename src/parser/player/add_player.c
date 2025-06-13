/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

static int determine_device(const char *device, player_t *player)
{
    if (!strcmp(device, "key")) {
        player->move = &player_movement_keyboard;
        player->move_select = &player_select_keyboard;
        return 0;
    }
    if (strlen(device) == 2 && device[0] == 'g') {
        if (my_str_isnum(&device[1])) {
            player->move = &player_movement_gamepad;
            player->move_select = &player_select_gamepad;
            return device[1] - '0';
        }
    }
    return -1;
}

int add_player_p(char **warray, wolf_context_t *context)
{
    player_t *player = (player_t *) 0;

    if (my_len_word_array(warray) < 6) {
        return ERROR;
    }
    context->n_players++;
    context->players = realloc(context->players,
        sizeof(player_t *) * context->n_players);
    if (create_player(&context->players[context->n_players - 1],
        context->n_players - 1, context->view->videomode) == ERROR) {
        return ERROR;
    }
    player = context->players[context->n_players - 1];
    player->device = determine_device(warray[4], player);
    player->param.fov = DEG_TO_RAD(my_getnbr(warray[3]));
    player->name = strdup(warray[1]);
    player->character = get_character(context, warray[5]);
    return OK;
}
