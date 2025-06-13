/*
** EPITECH PROJECT, 2024
** buttons_fonction
** File description:
** fonction buttons
*/

#include "selection_buttons.h"

static void handle_button_release(selection_t *selection, int total_buttons)
{
    button_t *btn;

    for (int i = 0; i < total_buttons; i++) {
        btn = &selection->buttons[i];
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

static void check_presse_buttons(selection_t *selection, int total_buttons)
{
    for (int i = 0; i < total_buttons; i++) {
        selection->buttons[i].is_pressed = selection->buttons[i].is_hovered;
        if (selection->buttons[i].is_hovered) {
            sfRectangleShape_setFillColor(selection->buttons[i].shape,
                selection->buttons[i].color);
        }
    }
}

static void check_hover_buttons(wolf_context_t *window, sfVector2f mouse_pos)
{
    button_t *btn;
    char change_cursor = 0;
    char hovered;

    for (int i = 0; i < window->n_players + 4; i++) {
        btn = &window->selection->buttons[i];
        hovered = is_mouse_over_button(btn->shape, mouse_pos);
        if (!btn->is_pressed) {
            sfRectangleShape_setFillColor(btn->shape, hovered ?
            sfColor_fromRGB(141, 141, 141) : btn->color
            );
        }
        btn->is_hovered = hovered;
        if (hovered)
            change_cursor = 1;
    }
    sfRenderWindow_setMouseCursor(window->view->window, change_cursor ?
        window->view->cursor_hand : window->view->cursor_arrow);
}

void selection_handle_mouse(wolf_context_t *window)
{
    int total_buttons = window->n_players + 4;

    if (window->evt.type == sfEvtMouseMoved) {
        window->selection->mouse_pos =
            sfRenderWindow_mapPixelToCoords(window->view->window,
            sfMouse_getPositionRenderWindow(window->view->window),
            sfRenderWindow_getDefaultView(window->view->window));
        check_hover_buttons(window, window->selection->mouse_pos);
    }
    if (window->evt.type == sfEvtMouseButtonPressed &&
        window->evt.mouseButton.button == sfMouseLeft) {
        check_presse_buttons(window->selection, total_buttons);
    }
    if (window->evt.type == sfEvtMouseButtonReleased &&
        window->evt.mouseButton.button == sfMouseLeft) {
        handle_button_release(window->selection, total_buttons);
    }
}
