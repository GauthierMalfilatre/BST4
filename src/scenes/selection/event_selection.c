/*
** EPITECH PROJECT, 2024
** setting wolf3d
** File description:
** player selection handling
*/
#include "sound.h"
#include "selection.h"
#include "./buttons/selection_buttons.h"

static const ptr_fonc_change_t actions[] = {
    NULL,
    change_character,
    change_team
};

void change_character(wolf_context_t *window, int i)
{
    if (window->selection->index_players[i] >= window->n_chars)
        window->selection->index_players[i] = 0;
    if (window->selection->index_players[i] < 0)
        window->selection->index_players[i] = window->n_chars - 1;
    play_force(window->characters[window->selection->index_players[i]]->
        voicelines.selection);
    sfSprite_setTexture(
        window->selection->buttons[i].character,
        window->characters[
        window->selection->index_players[i]]->apparance->texture,
        sfFalse
    );
}

void change_team(wolf_context_t *window, int i)
{
    player_t *player = window->players[i];
    int max_teams = 1;

    if (window->mode >= 0 && window->mode < 2)
        max_teams = max_teams_per_mode[window->mode];
    if (player->equipe < 0)
        player->equipe = max_teams - 1;
    else if (player->equipe >= max_teams)
        player->equipe = 0;
    sfRectangleShape_setFillColor(
        window->selection->buttons[i].shape,
        team_colors[player->equipe]);
    window->selection->buttons[i].color = team_colors[player->equipe];
}

static char is_selection_ready(selection_t *selection)
{
    return sfTime_asSeconds(
        sfClock_getElapsedTime(selection->player_selection_clocks)) >=
        COOLDOWN_TIME;
}

static void handle_player_selection(wolf_context_t *window)
{
    player_t *player;
    int result;

    for (int i = 0; i < window->n_players; i++) {
        player = window->players[i];
        if (player->device == -1)
            continue;
        result = player->move_select(
            player,
            &window->selection->index_players[i],
            &player->equipe);
        if (result <= 0 || result > 2)
            continue;
        if (actions[result])
            actions[result](window, i);
    }
    sfClock_restart(window->selection->player_selection_clocks);
}

void event_key_selection(wolf_context_t *window)
{
    if (is_selection_ready(window->selection)) {
        handle_player_selection(window);
    }
}
