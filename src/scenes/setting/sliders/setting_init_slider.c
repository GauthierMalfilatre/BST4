/*
** EPITECH PROJECT, 2024
** buttons_init
** File description:
** initialize all slider
*/

#include "setting_sliders.h"

static slider_t create_slider(sfVector2f position, sfVector2f size,
    unsigned int i)
{
    slider_t slider;

    slider.shape = sfRectangleShape_create();
    slider.is_hovered = 0;
    slider.is_pressed = 0;
    slider.is_select = 0;
    slider.slider_fonctions = slider_fonctions[i];
    if (!slider.shape) {
        perror("Error: Failed to create button shape");
        slider.shape = NULL;
    }
    sfRectangleShape_setOrigin(slider.shape,
        (sfVector2f){size.x / 2.0f, size.y / 2.0f});
    sfRectangleShape_setSize(slider.shape, size);
    sfRectangleShape_setFillColor(slider.shape, sfBlack);
    sfRectangleShape_setPosition(slider.shape, position);
    return slider;
}

static sfRectangleShape *create_slider_shape(sfVector2f slider_pos,
    sfVector2f slider_size, unsigned int percentage)
{
    sfRectangleShape *slider_button = sfRectangleShape_create();
    sfVector2f size = {slider_size.x * 0.05f, slider_size.y};
    sfVector2f position = {
        slider_pos.x - (slider_size.x / 2.0f) + size.x / 2.0f, slider_pos.y
    };

    if (!slider_button)
        return NULL;
    position.x += (slider_size.x - size.x) * (percentage / 100.0f);
    sfRectangleShape_setSize(slider_button, size);
    sfRectangleShape_setOrigin(slider_button, (sfVector2f){
        size.x / 2.0f,
        size.y / 2.0f
    });
    sfRectangleShape_setPosition(slider_button, position);
    sfRectangleShape_setFillColor(slider_button, sfWhite);
    return slider_button;
}

void init_setting_sliders(wolf_context_t *window)
{
    sfFloatRect b_shape;
    sfVector2f position;
    sfVector2f size;

    window->setting->sliders = malloc(sizeof(slider_t) * nb_sliders_count);
    if (!window->setting->sliders)
        return;
    for (int i = 0; i < nb_sliders_count; i++) {
        b_shape =
        sfRectangleShape_getGlobalBounds(window->setting->buttons[i].shape);
        size = (sfVector2f){b_shape.width * 0.4f, b_shape.height * 0.5f};
        position = (sfVector2f){
            b_shape.left + b_shape.width - (size.x / 2.0f) * 1.1f,
            b_shape.top + b_shape.height / 2.0f};
        window->setting->sliders[i] = create_slider(position, size, i);
        window->setting->sliders[i].shape_slider =
        create_slider_shape(position, size,
            value_to_percentage[i](window->setting->setting[i]));
    }
}
