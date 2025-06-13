/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Event gestion for bst scene.
*/
#include "wolf.h"
#include "scenes.h"

void reinit_game(wolf_context_t *context)
{
    if (context->mode != BS_GO) {
        return;
    }
    for (int i = 0; i < context->n_players; i++) {
        spawn(context->players[i], context);
    }
    destroy_blacksheep(context->bs);
    if (!create_blacksheep(context)) {
        exit(84);
    }
    spawn_blacksheep(context);
}

static void handle_presse(wolf_context_t *context)
{
    sfBool enter_pressed = sfKeyboard_isKeyPressed(sfKeyEnter) ||
        sfJoystick_isButtonPressed(0, 1);
    sfBool escape_pressed = sfKeyboard_isKeyPressed(sfKeyEscape) ||
        sfJoystick_isButtonPressed(0, 2);

    if (enter_pressed) {
        reinit_game(context);
        change_scene(context->mode == HILL || (context->wins.x >= 6 ||
            context->wins.y >= 6)
            ? SELECTION_SCENE : GAME_BST_SCENE, context);
    }
    if (escape_pressed)
        change_scene(MENU_SCENE, context);
}

void interlude_event(wolf_context_t *context)
{
    if (!context)
        return;
    if (context->evt.type == sfEvtClosed)
        sfRenderWindow_close(context->view->window);
    handle_presse(context);
}
