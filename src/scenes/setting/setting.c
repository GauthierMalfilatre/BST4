/*
** EPITECH PROJECT, 2024
** setting wolf3d
** File description:
** setting wolf3d
*/

#include "scenes.h"
#include "setting.h"

int setting_init(wolf_context_t *window)
{
    window->setting = malloc(sizeof(setting_t));
    if (!window->setting)
        return ERROR;
    memset(window->setting, 0, sizeof(setting_t));
    init_setting_param(window);
    init_setting_background(window);
    init_setting_text(window);
    init_setting_buttons(window);
    create_bottom_buttons(window);
    init_setting_sliders(window);
    return OK;
}

void setting_update(wolf_context_t *window)
{
    slider_fonctions_setting(window);
    button_fonctions_setting(window);
}

void setting_event(wolf_context_t *window)
{
    if (window->evt.type == sfEvtClosed) {
        sfRenderWindow_close(window->view->window);
        return;
    }
    if (window->evt.type == sfEvtKeyPressed &&
        window->evt.key.code == sfKeyEscape) {
        change_scene(MENU_SCENE, window);
        return;
    }
    setting_handle_mouse(window);
}

void setting_draw(wolf_context_t *window)
{
    if (window->setting->states.shader)
        setup_shader(window);
    sfRenderWindow_clear(window->view->window, sfBlack);
    if (window->setting->background)
        sfRenderWindow_drawRectangleShape(window->view->window,
            window->setting->background, &window->setting->states);
    sfRenderWindow_drawText(window->view->window,
        window->setting->text_setting, NULL);
    draw_buttons_setting(window);
    draw_sliders_setting(window);
}

void setting_destroy(wolf_context_t *window)
{
    if (!window->setting)
        return;
    destroy_all_buttons_setting(window->setting);
    destroy_all_sliders_setting(window->setting);
    if (window->setting->background)
        sfRectangleShape_destroy(window->setting->background);
    if (window->setting->texture_bg)
        sfTexture_destroy(window->setting->texture_bg);
    sfClock_destroy(window->setting->clock);
    sfFont_destroy(window->setting->font);
    sfText_destroy(window->setting->text_setting);
    free(window->setting);
}
