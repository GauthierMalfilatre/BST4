/*
** EPITECH PROJECT, 2024
** setting button
** File description:
** setting button header
*/

#ifndef MENU_BUTTONS_H
    #define MENU_BUTTONS_H

    #include "../setting.h"

    // Menu buttons index
    #define B_RESOLUTION 0
    #define B_FRAMERATE 1
    #define B_SOUND 2
    #define B_MUSIC 3
    #define B_SENSIBILITE 4
    #define B_FULLSCREEN 5
    #define B_BACK 6
    #define B_APPLY 7

typedef void (*ptr_fonc_t)(wolf_context_t *);

// Button structure
typedef struct button_s {
    sfRectangleShape *shape;
    sfText *text;
    sfColor color;
    char is_hovered;
    char is_pressed;
    char is_select;
    void (*button_fonc)(wolf_context_t *);
} button_t;

// Button functions
void null_fonc(wolf_context_t *window);
void fullscreen(wolf_context_t *window);
void back(wolf_context_t *window);
void apply(wolf_context_t *window);

// Function pointer array and button text
static const ptr_fonc_t b_fonctions[] =
{&null_fonc, &null_fonc, &null_fonc, &null_fonc, &null_fonc,
    &fullscreen, &back, &apply};
static const char *text_help[] __attribute__((unused)) =
{"resolution: ", "framerate: ", "sound: ",
    "music: ", "sensibilite: ", "fullscreen: ", "back", "apply"};
static const char *text_qualifer[] __attribute__((unused)) =
{"p", "FPS", "%", "%", "%"};
static const int nb_buttons_count = sizeof(b_fonctions) /
sizeof(b_fonctions[0]);

#endif // MENU_BUTTONS_H
