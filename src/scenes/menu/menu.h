/*
** EPITECH PROJECT, 2024
** menu
** File description:
** menu header
*/

#ifndef MENU_H
    #define MENU_H

    #include "wolf.h"

typedef struct menu_s {
    unsigned int id_scene;
    sfTexture *texture_bg_menu;
    sfSprite *background_menu;
    sfText *text_menu;
    sfFont *font;
    button_t *buttons;
    unsigned int font_size;
    unsigned char nb_players;
} menu_t;

// Initialization functions
void init_menu_background(wolf_context_t *window);
void init_menu_buttons(wolf_context_t *window);
void init_menu_text(wolf_context_t *window);
void init_start_buttons(wolf_context_t *window);

// Draw fonctions
void draw_buttons(wolf_context_t *window);
void draw_start_buttons(wolf_context_t *window);

// Destroy fonctions
void destroy_all_buttons(menu_t *menu);
void destroy_all_start_buttons(menu_t *menu);

// Event fonctions
void menu_handle_mouse(wolf_context_t *window);
void start_menu_handle_mouse(wolf_context_t *window);

// Update fonctions
void button_fonctions(wolf_context_t *window);
void button_start_fonctions(wolf_context_t *window);

#endif // MENU_H
