/*
** EPITECH PROJECT, 2024
** buttons_fonction
** File description:
** fonction buttons
*/

#include "setting_buttons.h"
#include "scenes.h"
#include "sound.h"

void button_fonctions_setting(wolf_context_t *window)
{
    for (int i = B_FULLSCREEN; i < nb_buttons_count; i++) {
        if (window->setting->buttons[i].is_select == 1) {
            play_sound(window->w_sound.sound_click);
            window->setting->buttons[i].is_select = 0;
            window->setting->buttons[i].button_fonc(window);
            return;
        }
        window->setting->buttons[i].is_select = 0;
    }
}

void null_fonc(wolf_context_t *window)
{
    (void)window;
    return;
}

void fullscreen(wolf_context_t *window)
{
    char buffer[32];

    window->setting->setting[SETTING_FULLSCREEN] =
    !window->setting->setting[SETTING_FULLSCREEN];
    snprintf(buffer, sizeof(buffer), "%s%s", text_help[B_FULLSCREEN],
    window->setting->setting[SETTING_FULLSCREEN] ? "On" : "Off");
    sfText_setString(window->setting->buttons[B_FULLSCREEN].text, buffer);
}

void back(wolf_context_t *window)
{
    change_scene(MENU_SCENE, window);
}

static void save_settings(wolf_context_t *window)
{
    FILE *fd = fopen(SETTING_PATH, "r+");

    if (!fd) {
        fprintf(stderr, "failed to open save file\n");
        return;
    }
    for (unsigned int i = 0; i < size_setting_table; i++) {
        fprintf(fd, "%s=%d\n", setting_table[i].name,
            window->setting->setting[setting_table[i].id]);
    }
    fclose(fd);
}

static void set_sound(wolf_context_t *window)
{
    window->w_setting[W_SOUND] = window->setting->setting[SETTING_SOUND];
    window->w_setting[W_MUSIC] = window->setting->setting[SETTING_MUSIC];
    sfMusic_setVolume(window->w_sound.music, window->w_setting[W_MUSIC]);
    sfSound_setVolume(window->w_sound.sound_click, window->w_setting[W_SOUND]);
    window->w_setting[W_SENSIBILITE] =
        window->setting->setting[SETTING_SENSIBILITE];
}

static unsigned int get_width_screen(wolf_context_t *window,
    unsigned int new_res)
{
    float ratio = 1920.f / 1080.f;

    (void)(window);
    return (unsigned int)(new_res * ratio);
}

void apply(wolf_context_t *window)
{
    char reset_window = 0;
    unsigned int new_resolution = window->setting->setting[SETTING_RESOLUTION];
    unsigned int new_fullscreen = window->setting->setting[SETTING_FULLSCREEN];
    unsigned int new_framerate = window->setting->setting[SETTING_FRAMERATE];

    save_settings(window);
    if (window->view->videomode.height != new_resolution)
        reset_window = 1;
    if (new_fullscreen != window->w_setting[W_FULLSCREEN]) {
        window->w_setting[W_FULLSCREEN] = new_fullscreen;
        reset_window = 1;
    }
    if (new_framerate != window->w_setting[W_FRAMERATE]) {
        window->w_setting[W_FRAMERATE] = new_framerate;
        reset_window = 1;
    }
    set_sound(window);
    if (reset_window)
        change_resolution(window,
            get_width_screen(window, new_resolution), new_resolution);
}
