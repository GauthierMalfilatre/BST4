/*
** EPITECH PROJECT, 2024
** buttons_fonction
** File description:
** fonction buttons
*/

#include "start_menu.h"
#include "../buttons_scene.h"
#include "sound.h"
#include "scenes.h"
#include "parser.h"

void button_start_fonctions(wolf_context_t *window)
{
    for (int i = 0; i < nb_buttons_count; i++) {
        if (window->menu->buttons[i].is_select == 1) {
            play_sound(window->w_sound.sound_click);
            window->menu->buttons[i].is_select = 0;
            window->menu->buttons[i].button_fonc(window);
            return;
        }
        window->menu->buttons[i].is_select = 0;
    }
}

static void fill_teams(wolf_context_t *context)
{
    if (context->n_players < 2 || context->n_players > 4) {
        return;
    }
    context->players[0]->equipe = 0;
    context->players[1]->equipe = 1;
    if (context->n_players > 2) {
        context->players[2]->equipe = context->mode == BS_GO ? 1 : 2;
    }
    if (context->n_players > 3) {
        if (context->mode == BS_GO) {
            context->players[2]->equipe = 0;
        }
        context->players[3]->equipe = context->mode == BS_GO ? 1 : 3;
    }
}

static void create_all_players(wolf_context_t *window)
{
    char buffer[512];

    window->players = realloc(window->players, sizeof(player_t *) *
        window->n_players);
    for (int i = 0; i < window->n_players; i++) {
        create_player(&window->players[i], i, window->view->videomode);
        window->players[i]->character = window->characters[0];
        window->players[i]->device = i;
        window->players[i]->move = i ? &player_movement_gamepad :
            &player_movement_keyboard;
        window->players[i]->move_select = i ? &player_select_gamepad :
            &player_select_keyboard;
        sprintf(buffer, "Player %d", i + 1);
        window->players[i]->name = strdup(buffer);
    }
    fill_teams(window);
}

void play(wolf_context_t *window)
{
    if (window->menu->nb_players >= 2 && window->menu->nb_players <= 4) {
        window->n_players = window->menu->nb_players;
        create_all_players(window);
    } else {
        return;
    }
    change_scene(SELECTION_SCENE, window);
}

void multiplayer(wolf_context_t *window)
{
    char buffer[13];

    window->menu->nb_players++;
    if (window->menu->nb_players > 4) {
        window->menu->nb_players = 2;
    }
    snprintf(buffer, sizeof(buffer), "%d Players", window->menu->nb_players);
    update_text(window->menu->buttons[B_MULTIPLAYER].text, buffer);
}

void back_start(wolf_context_t *window)
{
    window->menu->nb_players = 0;
    buttons_scenes[window->menu->id_scene].destroy(window->menu);
    window->menu->id_scene = MAIN;
    buttons_scenes[window->menu->id_scene].init(window);
}

void mode_start(wolf_context_t *window)
{
    window->mode++;
    if (window->mode > HILL) {
        window->mode = BS_GO;
    }
    update_text(window->menu->buttons[B_MODE].text, name_mode[window->mode]);
    return;
}
