/*
** EPITECH PROJECT, 2024
** setting sliders
** File description:
** setting sliders header
*/

#ifndef MENU_SLIDERS_H
    #define MENU_SLIDERS_H

    #include "../setting.h"
    #include "../buttons/setting_buttons.h"

    #define GET_SHAPE(n) (window->setting->sliders[n])
    #define GET_BOUNDS(n) sfRectangleShape_getGlobalBounds(GET_SHAPE(n).shape)

typedef float (*ptr_fonc_percentage_t)(int value);
typedef void (*ptr_fonc_t)(wolf_context_t *window);

typedef struct slider_s {
    sfRectangleShape *shape;
    sfColor color_fond;
    sfRectangleShape *shape_slider;
    char is_hovered;
    char is_pressed;
    char is_select;
    void (*slider_fonctions)(wolf_context_t *);
    float (*value_to_percentage)(int value);
} slider_t;

// Slider fonctions
void resolution_slider(wolf_context_t *window);
void sound_slider(wolf_context_t *window);
void music_slider(wolf_context_t *window);
void sensibilite_slider(wolf_context_t *window);
void framerate_slider(wolf_context_t *window);

// Slider value to pos
float resolution_to_percentage(int value);
float framerate_to_percentage(int value);
float sound_to_percentage(int value);

static const ptr_fonc_percentage_t value_to_percentage[] =
{&resolution_to_percentage, &framerate_to_percentage,
    &sound_to_percentage, &sound_to_percentage, &sound_to_percentage};

static const ptr_fonc_t slider_fonctions[] =
{&resolution_slider, &framerate_slider, &sound_slider, &music_slider,
    &sensibilite_slider};

static const int nb_sliders_count = sizeof(slider_fonctions) /
sizeof(slider_fonctions[0]);

static const int resolutions[] = { 480, 720, 1080, 1440, 2160 };
static const int resolution_count = sizeof(resolutions) /
sizeof(resolutions[0]);

#endif // MENU_SLIDERS_H
