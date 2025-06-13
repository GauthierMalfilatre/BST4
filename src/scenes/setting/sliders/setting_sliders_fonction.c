/*
** EPITECH PROJECT, 2024
** buttons_fonction
** File description:
** fonction buttons
*/

#include "setting_sliders.h"
#include "scenes.h"

static void update_text_slider(button_t *button, const char *text, int value,
    const char *c)
{
    char str[32];

    snprintf(str, sizeof(str), "%s%d%s", text, value, c);
    sfText_setString(button->text, str);
}

static int handle_slider(wolf_context_t *window, int button_index)
{
    sfFloatRect bounds = GET_BOUNDS(button_index);
    float mouse_x = window->setting->mouse_pos.x;

    if (mouse_x < bounds.left)
        mouse_x = bounds.left;
    else if (mouse_x > bounds.left + bounds.width)
        mouse_x = bounds.left + bounds.width;
    sfRectangleShape_setPosition(GET_SHAPE(button_index).shape_slider,
        (sfVector2f){mouse_x, bounds.top + bounds.height / 2});
    return ((mouse_x - bounds.left) / bounds.width) * 100.0f;
}

void resolution_slider(wolf_context_t *window)
{
    int percentage = handle_slider(window, B_RESOLUTION);
    int index = (percentage * resolution_count) / 100;

    if (index >= resolution_count)
        index = resolution_count - 1;
    update_text_slider(&window->setting->buttons[B_RESOLUTION], "resolution: ",
        resolutions[index], "p");
    window->setting->setting[SETTING_RESOLUTION] = resolutions[index];
}

void framerate_slider(wolf_context_t *window)
{
    int percentage;

    percentage = MIN_FPS + (handle_slider(window, B_FRAMERATE) *
    (MAX_FPS - MIN_FPS)) / 100;
    update_text_slider(&window->setting->buttons[B_FRAMERATE], "framerate: ",
        percentage, " IPS");
    window->setting->setting[SETTING_FRAMERATE] = percentage;
}

void sound_slider(wolf_context_t *window)
{
    int percentage;

    percentage = handle_slider(window, B_SOUND);
    update_text_slider(&window->setting->buttons[B_SOUND], "sound: ",
        percentage, "%");
    window->setting->setting[SETTING_SOUND] = percentage;
}

void music_slider(wolf_context_t *window)
{
    int percentage;

    percentage = handle_slider(window, B_MUSIC);
    update_text_slider(&window->setting->buttons[B_MUSIC], "Music: ",
        percentage, "%");
    window->setting->setting[SETTING_MUSIC] = percentage;
}

void sensibilite_slider(wolf_context_t *window)
{
    int percentage;

    percentage = handle_slider(window, B_SENSIBILITE);
    update_text_slider(&window->setting->buttons[B_SENSIBILITE],
        "Sensibilite: ", percentage, "%");
    window->setting->setting[SETTING_SENSIBILITE] = percentage;
}
