/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** change resolution
*/

#include "wolf.h"
#include "scenes.h"

static void create_window(view_t *view, unsigned int fullscreen)
{
    sfUint32 flags = sfResize | sfClose;

    if (fullscreen)
        flags |= sfFullscreen;
    view->window = sfRenderWindow_create(
        view->videomode, PROGNAME, flags, 0);
    if (!view->window) {
        return;
    }
    view->win_size = sfRenderWindow_getSize(view->window);
    view->window_diagonal = sqrtf(
        view->win_size.x * view->win_size.x +
        view->win_size.y * view->win_size.y);
}

void change_resolution(wolf_context_t *window, unsigned int width,
    unsigned int height)
{
    scenes[window->current_scene].destroy(window);
    window->view->videomode.width = width;
    window->view->videomode.height = height;
    sfRenderWindow_destroy(window->view->window);
    window->view->win_size.x = width;
    window->view->win_size.y = height;
    create_window(window->view, window->w_setting[W_FULLSCREEN]);
    scenes[window->current_scene].init(window);
}
