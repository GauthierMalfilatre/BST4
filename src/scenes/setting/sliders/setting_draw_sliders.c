/*
** EPITECH PROJECT, 2024
** draw sliders
** File description:
** draw all sliders
*/

#include "setting_sliders.h"

void draw_sliders_setting(wolf_context_t *window)
{
    for (int i = 0; i < nb_sliders_count; i++) {
        if (window->setting->sliders[i].shape != NULL) {
            sfRenderWindow_drawRectangleShape(window->view->window,
                window->setting->sliders[i].shape, NULL);
        }
        if (window->setting->sliders[i].shape_slider != NULL) {
            sfRenderWindow_drawRectangleShape(window->view->window,
                window->setting->sliders[i].shape_slider, NULL);
        }
    }
}
