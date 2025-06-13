/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Parse main file for configuration
*/
#include "parser.h"
#include "wolf.h"

const point_parse_t parse_tab[PARSING_ACTIONS] = {
    {"W", &add_wall_p},
    {"TW", &add_temp_wall_p},
    {"T", &add_texture_p},
    {"P", &add_player_p},
    {"C", &add_character_p},
    {"MAP", &add_map_p},
    {"SP", &add_spawn_p},
    {"BSP", &add_bsp_p},
    {"S", &add_sound_p},
    {"STUFF", &add_stuff_p},
    {"HP", &add_hp_p},
    {"FL", &add_floor_p},
    {"@require", &builtin_require},
};

static int find_action(wolf_context_t *context, char *buffer)
{
    char **warray = my_str_to_word_array(buffer);

    if (!warray || !warray[0]) {
        return ERROR;
    }
    for (int i = 0; i < PARSING_ACTIONS; i++) {
        if (!my_strcmp(warray[0], parse_tab[i].command) && parse_tab[i].func) {
            return parse_tab[i].func(warray, context);
        }
    }
    my_free_word_array(warray);
    return OK;
}

int parse_ray_file(wolf_context_t *context, const char *path)
{
    FILE *fp = fopen(path, "r");
    char *buffer = (char *) 0;
    size_t size = 0;

    if (!fp) {
        fprintf(stderr, PROGNAME": Failed to read config file %s.\n", path);
        return ERROR;
    }
    for (int i = 1; getline(&buffer, &size, fp) != -1; i++) {
        if (buffer && (buffer[0] == '\n' || buffer[0] == '#'))
            continue;
        if (find_action(context, buffer) == ERROR) {
            fclose(fp);
            free(buffer);
            return ERROR;
        }
    }
    free(buffer);
    fclose(fp);
    return OK;
}
