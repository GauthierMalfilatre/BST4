/*
** EPITECH PROJECT, 2024
** shader
** File description:
** setup shader
*/

#include "setting.h"

void setup_shader(wolf_context_t *window)
{
    float time =
    sfTime_asSeconds(sfClock_getElapsedTime(window->setting->clock));

    sfShader_setFloatUniform((sfShader *)window->setting->states.shader,
    "time", time);
    sfShader_setVec2Uniform((sfShader *)window->setting->states.shader,
    "resolution", (sfGlslVec2){window->view->win_size.x,
        window->view->win_size.y});
    sfShader_setVec2Uniform((sfShader *)window->setting->states.shader,
    "mouse", (sfGlslVec2){window->setting->mouse_pos.x,
            window->setting->mouse_pos.y});
}
