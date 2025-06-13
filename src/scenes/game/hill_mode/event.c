/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Event gestion for bst scene.
*/
#include "wolf.h"
#include "scenes.h"

void hill_event(wolf_context_t *context)
{
    if (!context)
        return;
    if (context->evt.type == sfEvtClosed) {
        sfRenderWindow_close(context->view->window);
    }
    context->is_alt = sfKeyboard_isKeyPressed(sfKeyLAlt);
    sfRenderWindow_setMouseCursorVisible(context->view->window,
        context->is_alt);
    if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        change_scene(MENU_SCENE, context);
    }
}
