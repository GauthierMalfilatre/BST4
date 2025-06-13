/*
** EPITECH PROJECT, 2024
** destroy_buttons
** File description:
** destroy all buttons
*/

#include "setting_buttons.h"

static void destroy_one_button(button_t *btn)
{
    if (!btn)
        return;
    if (btn->shape)
        sfRectangleShape_destroy(btn->shape);
    if (btn->text)
        sfText_destroy(btn->text);
}

void destroy_all_buttons_setting(setting_t *setting)
{
    if (!setting || !setting->buttons)
        return;
    for (int i = 0; i < nb_buttons_count; i++) {
        destroy_one_button(&setting->buttons[i]);
    }
    free(setting->buttons);
    setting->buttons = NULL;
}
