/*
** EPITECH PROJECT, 2024
** buttons_init
** File description:
** initialize all buttons
*/

#include "setting_buttons.h"

void draw_buttons_setting(wolf_context_t *window)
{
    for (int i = 0; i < nb_buttons_count; i++) {
        if (window->setting->buttons[i].shape != NULL) {
            sfRenderWindow_drawRectangleShape(window->view->window,
                window->setting->buttons[i].shape, NULL);
        }
        if (window->setting->buttons[i].text != NULL) {
            sfRenderWindow_drawText(window->view->window,
                window->setting->buttons[i].text, NULL);
        }
    }
}
