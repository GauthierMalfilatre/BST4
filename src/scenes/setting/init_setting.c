/*
** EPITECH PROJECT, 2024
** init_setting
** File description:
** initialize setting
*/

#include "setting.h"

static sfShader *init_shader(sfTexture *texture_bg, sfVector2u win_size)
{
    sfShader *shader = sfShader_createFromFile(NULL, NULL,
        "./assets/setting_assets/background.frag");

    if (!shader) {
        printf("Shader load failed\n");
        return NULL;
    }
    sfShader_setTextureUniform(shader, "backgroundTexture", texture_bg);
    sfShader_setVec2Uniform(shader, "resolution",
        (sfVector2f){win_size.x, win_size.y});
    sfShader_setFloatUniform(shader, "time", 0.0f);
    sfShader_setVec2Uniform(shader, "mouse", (sfVector2f){0.0f, 0.0f});
    return shader;
}

void init_setting_background(wolf_context_t *window)
{
    window->setting->texture_bg =
    sfTexture_createFromFile("./assets/menu_assets/menu_background_2.png", 0);
    if (!window->setting->texture_bg) {
        printf("Texture load failed\n");
        return;
    }
    window->setting->background = sfRectangleShape_create();
    if (!window->setting->background) {
        printf("RectangleShape creation failed\n");
        return;
    }
    sfRectangleShape_setSize(window->setting->background,
        (sfVector2f){window->view->win_size.x, window->view->win_size.y});
    window->setting->clock = sfClock_create();
    window->setting->states = (sfRenderStates){
        sfBlendAlpha,
        sfTransform_Identity,
        NULL,
        init_shader(window->setting->texture_bg, window->view->win_size),
    };
}

void init_setting_text(wolf_context_t *window)
{
    sfFloatRect bounds;
    sfText *text;

    window->setting->font =
    sfFont_createFromFile("./assets/fonts/Silkscreen-Regular.ttf");
    window->setting->font_size = (0.015f * window->view->window_diagonal);
    text = sfText_create();
    sfText_setString(text, "Setting");
    sfText_setFont(text, window->setting->font);
    sfText_setColor(text, sfWhite);
    sfText_setCharacterSize(text, window->setting->font_size * 2);
    bounds = sfText_getLocalBounds(text);
    sfText_setOrigin(text, (sfVector2f){bounds.width / 2, bounds.height});
    sfText_setPosition(text,
        (sfVector2f){window->view->win_size.x / 2,
            window->view->win_size.y * 0.2});
    window->setting->text_setting = text;
}

void init_setting_param(wolf_context_t *window)
{
    window->setting->setting[SETTING_RESOLUTION] =
        window->view->videomode.height;
    window->setting->setting[SETTING_FRAMERATE] =
        window->w_setting[W_FRAMERATE];
    window->setting->setting[SETTING_SOUND] = window->w_setting[W_SOUND];
    window->setting->setting[SETTING_MUSIC] = window->w_setting[W_MUSIC];
    window->setting->setting[SETTING_FULLSCREEN] =
        window->w_setting[W_FULLSCREEN];
    window->setting->setting[SETTING_SENSIBILITE] =
        window->w_setting[W_SENSIBILITE];
}
