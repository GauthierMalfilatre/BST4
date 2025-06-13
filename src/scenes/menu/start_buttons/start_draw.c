/*
** EPITECH PROJECT, 2024
** buttons_init
** File description:
** initialize all buttons
*/

#include "start_menu.h"

void draw_start_buttons(wolf_context_t *window)
{
    for (int i = 0; i < nb_buttons_count; i++) {
        if (window->menu->buttons[i].shape != NULL) {
            sfRenderWindow_drawRectangleShape(window->view->window,
                window->menu->buttons[i].shape, NULL);
            sfRenderWindow_drawText(window->view->window,
                window->menu->buttons[i].text, NULL);
        }
    }
}
