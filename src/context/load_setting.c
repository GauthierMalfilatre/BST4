/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** load setting
*/

#include "wolf.h"

static char read_value(FILE *fp, const char *key, unsigned int *out)
{
    char *line = NULL;
    size_t len = 0;
    size_t key_len = strlen(key);
    char found = 0;

    while (getline(&line, &len, fp) != -1 && !found) {
        if (line[0] == '\n' || line[0] == '#')
            continue;
        if (strncmp(line, key, key_len) == 0 && line[key_len] == '=') {
            *out = (unsigned int)atoi(line + key_len + 1);
            found = 1;
        }
    }
    free(line);
    rewind(fp);
    return found;
}

static void load_sound(FILE *fd, wolf_context_t *context)
{
    if (!read_value(fd, "Sound", &context->w_setting[W_SOUND]) ||
        context->w_setting[W_SOUND] > MAX_SOUND)
        context->w_setting[W_SOUND] = 100;
    if (!read_value(fd, "Music", &context->w_setting[W_MUSIC]) ||
        context->w_setting[W_MUSIC] > MAX_SOUND)
        context->w_setting[W_MUSIC] = 100;
}

char load_settings(wolf_context_t *context)
{
    FILE *fd = fopen(SETTING_PATH, "r");

    if (!fd)
        return ERROR;
    if (!read_value(fd, "Framerate", &context->w_setting[W_FRAMERATE]) ||
        context->w_setting[W_FRAMERATE] < MIN_FPS ||
        context->w_setting[W_FRAMERATE] > MAX_FPS)
        context->w_setting[W_FRAMERATE] = 60;
    load_sound(fd, context);
    if (!read_value(fd, "Fullscreen", &context->w_setting[W_FULLSCREEN]) ||
        context->w_setting[W_FULLSCREEN] > 1)
        context->w_setting[W_FULLSCREEN] = 0;
    if (!read_value(fd, "Sensibilite", &context->w_setting[W_SENSIBILITE]) ||
        context->w_setting[W_SENSIBILITE] < MIN_SENSI ||
        context->w_setting[W_SENSIBILITE] > MAX_SENSI)
        context->w_setting[W_SENSIBILITE] = 50;
    fclose(fd);
    return OK;
}
