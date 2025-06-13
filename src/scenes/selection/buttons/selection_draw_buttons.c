/*
** EPITECH PROJECT, 2024
** buttons_init
** File description:
** initialize all buttons
*/

#include "selection_buttons.h"

void draw_buttons_selection(wolf_context_t *window)
{
    for (int i = 0; i < window->n_players + 4; i++) {
        if (window->selection->buttons[i].shape != NULL) {
            sfRenderWindow_drawRectangleShape(window->view->window,
                window->selection->buttons[i].shape, NULL);
        }
        if (i < window->n_players &&
            window->selection->buttons[i].character != NULL) {
            sfSprite_setTextureRect(window->selection->buttons[i].character,
                (sfIntRect){0, 0, 82, 128});
            sfRenderWindow_drawSprite(window->view->window,
                window->selection->buttons[i].character, NULL);
        }
        if (window->selection->buttons[i].text != NULL) {
            sfRenderWindow_drawText(window->view->window,
                window->selection->buttons[i].text, NULL);
        }
    }
}
