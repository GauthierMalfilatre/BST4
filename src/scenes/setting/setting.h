/*
** EPITECH PROJECT, 2024
** setting
** File description:
** setting header
*/

#ifndef SETTING_H
    #define SETTING_H

    #include "wolf.h"

    #define SETTING_RESOLUTION 0
    #define SETTING_FRAMERATE 1
    #define SETTING_SOUND 2
    #define SETTING_MUSIC 3
    #define SETTING_SENSIBILITE 4
    #define SETTING_FULLSCREEN 5

typedef struct slider_s slider_t;

typedef struct setting_entry_s {
    int id;
    const char *name;
} setting_entry_t;

typedef struct setting_s {
    sfRectangleShape *background;
    sfTexture *texture_bg;
    sfRenderStates states;
    sfClock *clock;
    sfText *text_setting;
    sfFont *font;
    button_t *buttons;
    slider_t *sliders;
    sfVector2f mouse_pos;
    unsigned int setting[6];
    unsigned int font_size;
} setting_t;

// Initialization functions
void init_setting_background(wolf_context_t *window);
void init_setting_buttons(wolf_context_t *window);
void init_setting_text(wolf_context_t *window);
void init_setting_sliders(wolf_context_t *window);
void init_setting_param(wolf_context_t *window);
void create_bottom_buttons(wolf_context_t *window);

// Draw functions
void setup_shader(wolf_context_t *window);
void draw_buttons_setting(wolf_context_t *window);
void draw_sliders_setting(wolf_context_t *window);

// Destroy functions
void destroy_all_buttons_setting(setting_t *setting);
void destroy_all_sliders_setting(setting_t *setting);

// Event functions
void setting_handle_mouse(wolf_context_t *window);
void check_hover_slider(wolf_context_t *window, sfVector2f mouse_pos);
void check_click_sliders(setting_t *setting);
void handle_slider_release(setting_t *setting);

// Update functions
void button_fonctions_setting(wolf_context_t *window);
void slider_fonctions_setting(wolf_context_t *window);

static const setting_entry_t setting_table[] = {
    { SETTING_FRAMERATE, "Framerate" },
    { SETTING_SOUND, "Sound" },
    { SETTING_MUSIC, "Music"},
    { SETTING_SENSIBILITE, "Sensibilite" },
    { SETTING_FULLSCREEN, "Fullscreen" },
};

static const unsigned int size_setting_table =
sizeof(setting_table) / sizeof(setting_table[0]);

#endif // SETTING_H
