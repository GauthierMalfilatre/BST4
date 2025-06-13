/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy wolf3d view.
*/
#include "wolf.h"

void destroy_view(view_t *view)
{
    if (!view) {
        return;
    }
    sfCursor_destroy(view->cursor_arrow);
    sfCursor_destroy(view->cursor_hand);
    sfRenderWindow_destroy(view->window);
    free(view);
    return;
}
