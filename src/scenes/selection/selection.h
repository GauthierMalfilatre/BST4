/*
** EPITECH PROJECT, 2024
** setting
** File description:
** setting header
*/

#ifndef SELECTION_H
    #define SELECTION_H

    #define COOLDOWN_TIME 0.2f

    #include "wolf.h"

typedef void (*ptr_fonc_change_t)(wolf_context_t *, int);

typedef struct selection_s {
    sfTexture *texture_bg_menu;
    sfSprite *background_menu;
    sfText *text_selection;
    sfRectangleShape *rect_map;
    sfText *text_map;
    sfClock *player_selection_clocks;
    sfFont *font;
    button_t *buttons;
    sfVector2f mouse_pos;
    int *index_players;
    int index_map;
    int font_size;
} selection_t;

// Initialization functions
void init_selection_background(wolf_context_t *window);
void init_selection_buttons(wolf_context_t *window);
void create_bottom_selection(wolf_context_t *window);
void init_selection_text(wolf_context_t *window);
void init_selection_map(wolf_context_t *window);
void create_arrow_buttons(wolf_context_t *window);

// Draw functions
void draw_buttons_selection(wolf_context_t *window);

// Destroy functions
void destroy_all_buttons_selection(selection_t *selection, int total_buttons);

// Event functions
void selection_handle_mouse(wolf_context_t *window);
void event_key_selection(wolf_context_t *window);

// Update functions
void button_fonctions_selection(wolf_context_t *window);

void change_character(wolf_context_t *window, int i);
void change_team(wolf_context_t *window, int i);

static const sfColor team_colors[] = {
    {255, 80, 80, 255},
    {80, 80, 255, 255},
    {80, 255, 80, 255},
    {255, 255, 100, 255},
};

static const int len_team_color = sizeof(team_colors) / sizeof(team_colors[0]);

static const int max_teams_per_mode[] = {
    [BS_GO] = 2,
    [HILL] = 4,
};

#endif // SELECTION_H
