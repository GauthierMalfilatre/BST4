/*
** EPITECH PROJECT, 2024
** setting wolf3d
** File description:
** setting wolf3d
*/

#include "selection.h"
#include "scenes.h"

static int count_joysticks(void)
{
    int i = 0;

    for (; i < sfJoystickCount && sfJoystick_isConnected(i); i++);
    return i;
}

int selection_init(wolf_context_t *window)
{
    if (!window)
        return ERROR;
    window->selection = calloc(1, sizeof(selection_t));
    if (!window->selection)
        return ERROR;
    init_selection_background(window);
    init_selection_text(window);
    init_selection_map(window);
    init_selection_buttons(window);
    create_bottom_selection(window);
    if (window->selection && window->selection->rect_map)
        create_arrow_buttons(window);
    window->selection->index_players = calloc(window->n_players, sizeof(int));
    if (count_joysticks() >= window->n_players) {
        for (int i = 0; i < window->n_players; i++) {
            window->players[i]->device++;
            window->players[i]->move = &player_movement_gamepad;
            window->players[i]->move_select = &player_select_gamepad;
        }
    }
    for (int i = 0; i < window->n_players; i++) {
        window->players[i]->score = 0;
        init_sdl(window->players[i]);
    }
    if (!window->selection->index_players)
        return ERROR;
    window->selection->player_selection_clocks = sfClock_create();
    if (!window->selection->player_selection_clocks)
        return ERROR;
    return OK;
}

void selection_update(wolf_context_t *window)
{
    button_fonctions_selection(window);
}

void selection_event(wolf_context_t *window)
{
    if (window->evt.type == sfEvtClosed) {
        sfRenderWindow_close(window->view->window);
        return;
    }
    if (window->evt.type == sfEvtKeyPressed ||
        window->evt.type == sfEvtJoystickMoved) {
        event_key_selection(window);
        return;
    }
    selection_handle_mouse(window);
}

void selection_draw(wolf_context_t *window)
{
    sfRenderWindow_clear(window->view->window, sfBlack);
    if (window->selection->background_menu)
        sfRenderWindow_drawSprite(window->view->window,
            window->selection->background_menu, NULL);
    if (window->selection->text_selection)
        sfRenderWindow_drawText(window->view->window,
        window->selection->text_selection, NULL);
    if (window->selection->rect_map)
        sfRenderWindow_drawRectangleShape(window->view->window,
            window->selection->rect_map, NULL);
    if (window->selection->text_map)
        sfRenderWindow_drawText(window->view->window,
            window->selection->text_map, NULL);
    draw_buttons_selection(window);
}

void selection_destroy(wolf_context_t *window)
{
    if (!window || !window->selection)
        return;
    destroy_all_buttons_selection(window->selection, window->n_players + 4);
    if (window->selection->background_menu)
        sfSprite_destroy(window->selection->background_menu);
    if (window->selection->texture_bg_menu)
        sfTexture_destroy(window->selection->texture_bg_menu);
    if (window->selection->text_selection)
        sfText_destroy(window->selection->text_selection);
    if (window->selection->rect_map)
        sfRectangleShape_destroy(window->selection->rect_map);
    if (window->selection->player_selection_clocks)
        sfClock_destroy(window->selection->player_selection_clocks);
    if (window->selection->text_map)
        sfText_destroy(window->selection->text_map);
    sfFont_destroy(window->selection->font);
    if (window->selection->index_players)
        free(window->selection->index_players);
    free(window->selection);
    window->selection = NULL;
}
