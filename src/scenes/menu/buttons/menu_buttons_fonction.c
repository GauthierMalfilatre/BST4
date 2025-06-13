/*
** EPITECH PROJECT, 2024
** buttons_fonction
** File description:
** fonction buttons
*/

#include "menu_buttons.h"
#include "../buttons_scene.h"
#include "scenes.h"
#include "sound.h"

void button_fonctions(wolf_context_t *window)
{
    for (int i = 0; i < nb_buttons_count; i++) {
        if (window->menu->buttons[i].is_select == 1) {
            play_sound(window->w_sound.sound_click);
            window->menu->buttons[i].is_select = 0;
            window->menu->buttons[i].button_fonc(window);
            return;
        }
        window->menu->buttons[i].is_select = 0;
    }
}

void start(wolf_context_t *window)
{
    buttons_scenes[window->menu->id_scene].destroy(window->menu);
    window->menu->id_scene = START;
    buttons_scenes[window->menu->id_scene].init(window);
}

void credit(wolf_context_t *window)
{
    change_scene(CREDIT_SCENE, window);
}

void quit(wolf_context_t *window)
{
    sfRenderWindow_close(window->view->window);
}

void setting(wolf_context_t *window)
{
    change_scene(SETTING_SCENE, window);
}
