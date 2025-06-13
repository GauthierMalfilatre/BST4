/*
** EPITECH PROJECT, 2024
** setting button
** File description:
** setting button header
*/

#ifndef SELECTION_BUTTONS_H
    #define SELECTION_BUTTONS_H

    #include "../selection.h"

    // Menu buttons index
    #define BACK_INDEX 0
    #define START_INDEX 1
    #define RIGHT_INDEX 2
    #define LEFT_INDEX 3
    #define RUMBLE_INDEX 4

    #define B_COLOR ((sfColor){139, 158, 183, 100})

typedef void (*ptr_fonc_t)(wolf_context_t *, int);

// Button structure
typedef struct button_s {
    sfRectangleShape *shape;
    sfText *text;
    sfSprite *character;
    sfColor color;
    char is_hovered;
    char is_pressed;
    char is_select;
    void (*button_fonc)(wolf_context_t *, int i);
} button_t;

// Button functions
void null_fonc(wolf_context_t *window, int i);
void back(wolf_context_t *window, int i);
void start_game(wolf_context_t *window, int i);
void map_right(wolf_context_t *window, int i);
void map_left(wolf_context_t *window, int i);
void rumble(wolf_context_t *window, int i);

// Function pointer array and button text
static const ptr_fonc_t b_fonctions[] =
{&back, &start_game, &map_right, &map_left, &rumble};

#endif // SELECTION_BUTTONS_H
