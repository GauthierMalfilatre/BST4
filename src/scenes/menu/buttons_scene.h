/*
** EPITECH PROJECT, 2024
** scene
** File description:
** scene header
*/

#ifndef BUTTONS_SCENE_H
    #define BUTTONS_SCENE_H

    #include "menu.h"

enum menu_scene_e {
    MAIN, START
};

typedef struct menu_ref {
    unsigned int id;
    void (*init)(wolf_context_t *);
    void (*event)(wolf_context_t *);
    void (*fonction)(wolf_context_t *);
    void (*draw)(wolf_context_t *);
    void (*destroy)(menu_t *);
} menu_ref_t;

static const menu_ref_t buttons_scenes[] = {
    {
        MAIN,
        &init_menu_buttons,
        &menu_handle_mouse,
        &button_fonctions,
        &draw_buttons,
        &destroy_all_buttons
    },
    {
        START,
        &init_start_buttons,
        &start_menu_handle_mouse,
        &button_start_fonctions,
        &draw_start_buttons,
        &destroy_all_start_buttons
    }
};

#endif //BUTTONS_SCENE_H
