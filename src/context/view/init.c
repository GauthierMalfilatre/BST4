/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Create the main view for the Wolf3D game.
*/

#include "wolf.h"

int create_view(view_t **view, unsigned int fullscreen)
{
    sfUint32 flags = sfResize | sfClose;

    *view = malloc(sizeof(view_t));
    if (!*view)
        return ERROR;
    if (fullscreen)
        flags |= sfFullscreen;
    (*view)->cursor_arrow = sfCursor_createFromSystem(sfCursorArrow);
    (*view)->cursor_hand = sfCursor_createFromSystem(sfCursorHand);
    (*view)->videomode = sfVideoMode_getDesktopMode();
    (*view)->window = sfRenderWindow_create((*view)->videomode,
        PROGNAME, flags, NULL);
    if (!(*view)->window)
        return ERROR;
    (*view)->win_size = sfRenderWindow_getSize((*view)->window);
    (*view)->window_diagonal = sqrtf(
        (float)((*view)->win_size.x * (*view)->win_size.x +
                (*view)->win_size.y * (*view)->win_size.y));
    return OK;
}
