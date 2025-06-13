/*
** EPITECH PROJECT, 2024
** menu
** File description:
** menu header
*/

#ifndef MENU_BUTTONS_H
    #define MENU_BUTTONS_H

    #include "../menu.h"

    // Menu buttons index
    #define B_START  0
    #define B_QUIT   1
    #define B_SETTING 2
    #define B_CREDIT 3

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
void start(wolf_context_t *window);
void quit(wolf_context_t *window);
void setting(wolf_context_t *window);
void credit(wolf_context_t *window);

typedef void (*ptr_fonc_t)(wolf_context_t *window);

// Function pointer array and button text
static const ptr_fonc_t b_fonctions[] = {&start, &setting, &credit, &quit};

static const char *text_help[] __attribute__((unused)) =
{"start", "setting", "credit", "quit"};

static const int nb_buttons_count = sizeof(b_fonctions) /
sizeof(b_fonctions[0]);

#endif // MENU_BUTTONS_H
