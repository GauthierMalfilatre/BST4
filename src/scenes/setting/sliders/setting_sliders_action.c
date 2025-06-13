/*
** EPITECH PROJECT, 2024
** sliders_actions
** File description:
** action slider mouse
*/

#include "setting_sliders.h"

void handle_slider_release(setting_t *setting)
{
    slider_t *slider;

    for (int i = 0; i < nb_sliders_count; i++) {
        slider = &setting->sliders[i];
        if (slider->is_pressed) {
            slider->is_select = 1;
            sfRectangleShape_setFillColor(slider->shape_slider, sfWhite);
        }
        slider->is_pressed = 0;
    }
}

void check_click_sliders(setting_t *setting)
{
    for (int i = 0; i < nb_sliders_count; i++) {
        setting->sliders[i].is_pressed = setting->sliders[i].is_hovered;
        if (setting->sliders[i].is_hovered) {
            sfRectangleShape_setFillColor(setting->sliders[i].shape_slider,
                sfRed);
        }
    }
}

void check_hover_slider(wolf_context_t *window, sfVector2f mouse_pos)
{
    slider_t *slider;
    char change_cursor = 0;
    char hovered = 0;

    for (int i = 0; i < nb_sliders_count; i++) {
        slider = &window->setting->sliders[i];
        hovered = is_mouse_over_button(slider->shape, mouse_pos);
        if (!slider->is_pressed)
            sfRectangleShape_setFillColor(slider->shape_slider, sfWhite);
        slider->is_hovered = hovered;
        if (hovered)
            change_cursor = 1;
    }
    sfRenderWindow_setMouseCursor(window->view->window, change_cursor ?
        window->view->cursor_hand : window->view->cursor_arrow);
}

void slider_fonctions_setting(wolf_context_t *window)
{
    for (int i = 0; i < nb_sliders_count; i++) {
        if (window->setting->sliders[i].is_pressed == 1) {
            window->setting->sliders[i].slider_fonctions(window);
        }
        window->setting->sliders[i].is_select = 0;
    }
}
