/*
** EPITECH PROJECT, 2024
** destroy_sliders
** File description:
** destroy all sliders
*/

#include "setting_sliders.h"

static void destroy_one_slider(slider_t *slider)
{
    if (!slider)
        return;
    if (slider->shape)
        sfRectangleShape_destroy(slider->shape);
    if (slider->shape_slider)
        sfRectangleShape_destroy(slider->shape_slider);
}

void destroy_all_sliders_setting(setting_t *setting)
{
    if (!setting || !setting->sliders)
        return;
    for (int i = 0; i < nb_sliders_count; i++) {
        destroy_one_slider(&setting->sliders[i]);
    }
    free(setting->sliders);
    setting->sliders = NULL;
}
