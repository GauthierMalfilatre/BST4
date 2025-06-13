/*
** EPITECH PROJECT, 2024
** buttons_fonction
** File description:
** fonction buttons
*/

#include "setting_buttons.h"

static void handle_button_release(setting_t *setting)
{
    button_t *btn;

    for (int i = 0; i < nb_buttons_count; i++) {
        btn = &setting->buttons[i];
        if (btn->is_pressed && btn->is_hovered) {
            btn->is_select = 1;
            btn->is_pressed = 0;
            sfRectangleShape_setFillColor(btn->shape,
                sfColor_fromRGB(141, 141, 141));
            return;
        }
        btn->is_pressed = 0;
    }
}

static void check_presse_buttons(setting_t *setting)
{
    for (int i = 0; i < nb_buttons_count; i++) {
        setting->buttons[i].is_pressed = setting->buttons[i].is_hovered;
        if (setting->buttons[i].is_hovered) {
            sfRectangleShape_setFillColor(setting->buttons[i].shape,
                setting->buttons[i].color);
        }
    }
}

static void check_hover_buttons(wolf_context_t *window, sfVector2f mouse_pos)
{
    button_t *btn;
    char hovered;

    for (int i = 0; i < nb_buttons_count; i++) {
        btn = &window->setting->buttons[i];
        hovered = is_mouse_over_button(btn->shape, mouse_pos);
        if (!btn->is_pressed) {
            sfRectangleShape_setFillColor(btn->shape, hovered ?
            sfColor_fromRGB(141, 141, 141) : btn->color
            );
        }
        btn->is_hovered = hovered;
    }
}

void setting_handle_mouse(wolf_context_t *window)
{
    if (window->evt.type == sfEvtMouseMoved) {
        window->setting->mouse_pos =
            sfRenderWindow_mapPixelToCoords(window->view->window,
            sfMouse_getPositionRenderWindow(window->view->window),
            sfRenderWindow_getDefaultView(window->view->window));
        check_hover_buttons(window, window->setting->mouse_pos);
        check_hover_slider(window, window->setting->mouse_pos);
    }
    if (window->evt.type == sfEvtMouseButtonPressed &&
        window->evt.mouseButton.button == sfMouseLeft) {
        check_presse_buttons(window->setting);
        check_click_sliders(window->setting);
    }
    if (window->evt.type == sfEvtMouseButtonReleased &&
        window->evt.mouseButton.button == sfMouseLeft) {
        handle_button_release(window->setting);
        handle_slider_release(window->setting);
    }
}
