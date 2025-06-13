/*
** EPITECH PROJECT, 2024
** My_world
** File description:
** my_world
*/

#include "menu.h"
#include "buttons_scene.h"

int menu_init(wolf_context_t *window)
{
    window->menu = malloc(sizeof(menu_t));
    if (!window->menu)
        return ERROR;
    memset(window->menu, 0, sizeof(menu_t));
    window->menu->nb_players = 2;
    window->menu->id_scene = MAIN;
    init_menu_background(window);
    init_menu_text(window);
    buttons_scenes[window->menu->id_scene].init(window);
    return OK;
}

void menu_update(wolf_context_t *window)
{
    buttons_scenes[window->menu->id_scene].fonction(window);
}

void menu_event(wolf_context_t *window)
{
    if (window->evt.type == sfEvtClosed) {
        sfRenderWindow_close(window->view->window);
        return;
    }
    buttons_scenes[window->menu->id_scene].event(window);
}

void menu_draw(wolf_context_t *window)
{
    sfRenderWindow_clear(window->view->window, sfGreen);
    sfRenderWindow_drawSprite(window->view->window,
        window->menu->background_menu, NULL);
    sfRenderWindow_drawText(window->view->window,
        window->menu->text_menu, NULL);
    buttons_scenes[window->menu->id_scene].draw(window);
}

void menu_destroy(wolf_context_t *window)
{
    if (!window->menu)
        return;
    buttons_scenes[window->menu->id_scene].destroy(window->menu);
    if (window->menu->background_menu)
        sfSprite_destroy(window->menu->background_menu);
    if (window->menu->texture_bg_menu)
        sfTexture_destroy(window->menu->texture_bg_menu);
    sfFont_destroy(window->menu->font);
    sfText_destroy(window->menu->text_menu);
    free(window->menu);
    return;
}
