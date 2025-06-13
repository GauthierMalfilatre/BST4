/*
** EPITECH PROJECT, 2024
** menu
** File description:
** menu header
*/

#ifndef START_BUTTONS_H
    #define START_BUTTONS_H

    #include "../menu.h"

    // Menu buttons index
    #define B_SOLO  0
    #define B_MULTIPLAYER 1
    #define B_MODE 2
    #define B_BACK 3

// Button structure
typedef struct button_s {
    sfRectangleShape *shape;
    sfText *text;
    sfVector2f default_size;
    char is_hovered;
    char is_pressed;
    char is_select;
    void (*button_fonc)(wolf_context_t *);
} button_t;

// Button functions
void play(wolf_context_t *window);
void multiplayer(wolf_context_t *window);
void mode_start(wolf_context_t *window);
void back_start(wolf_context_t *window);

typedef void (*ptr_fonc_t)(wolf_context_t *window);

// Function pointer array and button text
static const ptr_fonc_t b_fonctions[] = {
    &play, &multiplayer, &mode_start, &back_start
};

static const char *text_help[] __attribute__((unused)) =
{"play", "2 players", "BS:GO", "back"};

static const char *name_mode[] __attribute__((unused)) =
{"BS:GO", "HILL"};

static const int nb_buttons_count =
sizeof(b_fonctions) / sizeof(b_fonctions[0]);

#endif // START_BUTTONS_H
