/*
** EPITECH PROJECT, 2024
** menu
** File description:
** menu action buttons
*/

#include "start_menu.h"

static void handle_button_release(menu_t *menu)
{
    button_t *btn;

    for (int i = 0; i < nb_buttons_count; i++) {
        btn = &menu->buttons[i];
        if (btn->is_pressed && btn->is_hovered) {
            btn->is_select = 1;
            btn->is_pressed = 0;
            sfRectangleShape_setScale(btn->shape, (sfVector2f){1.1f, 1.1f});
            return;
        }
        btn->is_pressed = 0;
    }
}

static void check_presse_buttons(menu_t *menu)
{
    for (int i = 0; i < nb_buttons_count; i++) {
        menu->buttons[i].is_pressed = menu->buttons[i].is_hovered;
        if (menu->buttons[i].is_hovered) {
            sfRectangleShape_setScale(menu->buttons[i].shape,
                (sfVector2f){1.0f, 1.0f});
        }
    }
}

static void check_hover_buttons(wolf_context_t *window, sfVector2f mouse_pos)
{
    button_t *btn;
    char change_cursor = 0;
    char hovered;

    for (int i = 0; i < nb_buttons_count; i++) {
        btn = &window->menu->buttons[i];
        hovered = is_mouse_over_button(btn->shape, mouse_pos);
        if (!btn->is_pressed) {
            sfRectangleShape_setScale(btn->shape, (sfVector2f){
                hovered ? 1.1f : 1.0f, hovered ? 1.1f : 1.0f});
            sfText_setCharacterSize(btn->text, window->menu->font_size *
                (hovered ? 1.1f : 1.0f));
            update_text_pos(btn->shape, btn->text);
        }
        btn->is_hovered = hovered;
        if (hovered)
            change_cursor = 1;
    }
    sfRenderWindow_setMouseCursor(window->view->window, change_cursor ?
        window->view->cursor_hand : window->view->cursor_arrow);
}

void start_menu_handle_mouse(wolf_context_t *window)
{
    if (window->evt.type == sfEvtMouseMoved) {
        check_hover_buttons(window,
        sfRenderWindow_mapPixelToCoords(window->view->window,
        sfMouse_getPositionRenderWindow(window->view->window),
        sfRenderWindow_getDefaultView(window->view->window)));
    }
    if (window->evt.type == sfEvtMouseButtonPressed &&
        window->evt.mouseButton.button == sfMouseLeft) {
        check_presse_buttons(window->menu);
    }
    if (window->evt.type == sfEvtMouseButtonReleased &&
        window->evt.mouseButton.button == sfMouseLeft) {
        handle_button_release(window->menu);
    }
}
