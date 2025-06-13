/*
** EPITECH PROJECT, 2024
** destroy_buttons
** File description:
** destroy all buttons
*/

#include "selection_buttons.h"

static void destroy_one_button(button_t *btn)
{
    if (!btn)
        return;
    if (btn->shape) {
        sfRectangleShape_destroy(btn->shape);
        btn->shape = NULL;
    }
    if (btn->text) {
        sfText_destroy(btn->text);
        btn->text = NULL;
    }
    if (btn->character) {
        sfSprite_destroy(btn->character);
        btn->character = NULL;
    }
}

void destroy_all_buttons_selection(selection_t *selection, int total_buttons)
{
    if (!selection || !selection->buttons)
        return;
    for (int i = 0; i < total_buttons; i++) {
        destroy_one_button(&selection->buttons[i]);
    }
    free(selection->buttons);
    selection->buttons = NULL;
}
