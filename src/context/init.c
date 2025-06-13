/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Initializes the main Wolf3D game context and resources.
*/

#include "wolf.h"
#include "sound.h"
#include "parser.h"
#include "scenes.h"
#include <time.h>

static int init_context_struct(wolf_context_t *context)
{
    if (!context)
        return ERROR;
    memset(context, 0, sizeof(wolf_context_t));
    if (load_settings(context) == ERROR) {
        fprintf(stderr, "Failed to load settings.\n");
        return ERROR;
    }
    if (create_view(&context->view, context->w_setting[W_FULLSCREEN]) != OK)
        return ERROR;
    create_sound(context);
    play_music(context, MENU_MUSIC, sfTrue);
    context->current_scene = MENU_SCENE;
    return OK;
}

static void init_post_parse_data(wolf_context_t *context)
{
    srand(time(NULL));
    context->is_alt = 0;
    context->textures = NULL;
    context->n_players = 0;
    context->players = NULL;
    context->n_chars = 0;
    context->characters = NULL;
    context->n_map = 0;
    context->maps = NULL;
    context->cmap = NULL;
    context->wins = (sfVector2i){0, 0};
}

int create_context(wolf_context_t **context, const char *config_file)
{
    if (!context || !config_file)
        return ERROR;
    *context = malloc(sizeof(wolf_context_t));
    if (!(*context))
        return ERROR;
    init_post_parse_data(*context);
    if (init_context_struct(*context) != OK) {
        destroy_context(*context);
        return ERROR;
    }
    if (parse_ray_file(*context, config_file) != OK) {
        destroy_context(*context);
        return ERROR;
    }
    if (scenes[(*context)->current_scene].init(*context) != OK) {
        destroy_context(*context);
        return ERROR;
    }
    (*context)->bs = create_blacksheep(*context);
    return OK;
}
