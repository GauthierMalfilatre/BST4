/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Header file for scenes.
*/
#ifndef SCENES_WOLF_3D_H
    #define SCENES_WOLF_3D_H

    #include "wolf.h"

/* Enumeration for type of scene */
typedef enum scene_type_e {
    MENU_SCENE,
    SETTING_SCENE,
    CREDIT_SCENE,
    SELECTION_SCENE,
    GAME_BST_SCENE,
    INTERLUDE_SCENE,
    GAME_HILL_SCENE,
} scene_type_t;

typedef struct ref {
    int id;
    int (*init)(wolf_context_t *);
    void (*update)(wolf_context_t *);
    void (*event)(wolf_context_t *);
    void (*draw)(wolf_context_t *);
    void (*destroy)(wolf_context_t *);
} ref_t;

static const ref_t scenes[] =
{
    {MENU_SCENE, &menu_init, &menu_update,
        &menu_event, &menu_draw, &menu_destroy},
    {SETTING_SCENE, &setting_init, &setting_update, &setting_event,
        &setting_draw, &setting_destroy},
    {CREDIT_SCENE, &credit_init, &credit_update, &credit_event, &credit_draw,
        &credit_destroy},
    {SELECTION_SCENE, &selection_init, &selection_update,
        &selection_event, &selection_draw, &selection_destroy},
    {GAME_BST_SCENE, &bst_init, &bst_update,
        &bst_event, &bst_draw, &bst_destroy},
    {INTERLUDE_SCENE, &interlude_init, &interlude_update, &interlude_event,
        &interlude_draw, &interlude_destroy},
    {GAME_HILL_SCENE, &hill_init, &hill_update, &hill_event, &hill_draw,
        &hill_destroy},
};

#endif /* SCENES_WOLF_3D_H */
