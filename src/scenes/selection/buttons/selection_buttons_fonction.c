/*
** EPITECH PROJECT, 2024
** buttons_fonction
** File description:
** fonction buttons
*/

#include "selection_buttons.h"
#include "sound.h"
#include "scenes.h"

void button_fonctions_selection(wolf_context_t *window)
{
    for (int i = 0; i < window->n_players + 4; i++) {
        if (window->selection->buttons[i].is_select == 1 &&
            window->selection->buttons[i].button_fonc != NULL) {
            play_sound(window->w_sound.sound_click);
            window->selection->buttons[i].is_select = 0;
            window->selection->buttons[i].button_fonc(window, i);
            return;
        }
        window->selection->buttons[i].is_select = 0;
    }
}

static void spawn_all(wolf_context_t *window)
{
    window->wins = (sfVector2i){0, 0};
    for (int i = 0; i < window->n_players; i++) {
        init_player_voicelines(window->players[i], window);
        spawn(window->players[i], window);
    }
    spawn_blacksheep(window);
}

void start_game(wolf_context_t *window, int i)
{
    (void) i;
    for (int i = 0; i < window->n_players; i++) {
        window->players[i]->character =
        window->characters[window->selection->index_players[i]];
    }
    if (window->selection->index_map >= 0 &&
        window->selection->index_map < window->n_map)
        window->cmap = window->maps[window->selection->index_map];
    spawn_all(window);
    for (sounds_t *s = window->w_sound.sounds; s; s = s->next) {
        sfSound_setVolume(s->sound, window->w_setting[W_SOUND]);
    }
    change_scene(window->mode == BS_GO ? GAME_BST_SCENE :
        GAME_HILL_SCENE, window);
}

void map_right(wolf_context_t *window, int i)
{
    (void) i;
    window->selection->index_map++;
    if (window->selection->index_map >= window->n_map)
        window->selection->index_map = 0;
    update_text(window->selection->text_map,
        window->maps[window->selection->index_map]->name);
    return;
}

void map_left(wolf_context_t *window, int i)
{
    (void) i;
    window->selection->index_map--;
    if (window->selection->index_map < 0)
        window->selection->index_map = window->n_map - 1;
    update_text(window->selection->text_map,
        window->maps[window->selection->index_map]->name);
    return;
}

void rumble(wolf_context_t *window, int i)
{
    if (i > 0 && i < window->n_players) {
        if (window->players[i]->sdl.h) {
            rumble_controller(window->players[i]);
        }
    }
    return;
}
