/*
** EPITECH PROJECT, 2025
** RAY4
** File description:
** Main file for ray engine v4
*/
#ifndef PARSER_WOLF_H
    #define PARSER_WOLF_H
    #define PARSING_ACTIONS 13
    #define BULTINS 1

    #include "wolf.h"

typedef struct point_parse_s {
    char *command;
    int (*func)();
} point_parse_t;

typedef struct skill_tab_s {
    char *command;
    int (*skill)();
    int (*endskill)();
    float skill_cooldown;
    float endskill_cooldown;
} skill_tab_t;

int add_wall(wall_t wall, maps_t *map);

int add_wall_p(char **warray, wolf_context_t *context);
int add_temp_wall_p(char **warray, wolf_context_t *context);
int add_player_p(char **warray, wolf_context_t *context);
int add_texture_p(char **warray, wolf_context_t *context);
int add_character_p(char **warray, wolf_context_t *context);
int add_map_p(char **warray, wolf_context_t *context);
int add_sound_p(char **warray, wolf_context_t *context);
int add_spawn_p(char **warray, wolf_context_t *context);
int add_stuff_p(char **warray, wolf_context_t *context);
int add_bsp_p(char **warray, wolf_context_t *context);
int add_hp_p(char **warray, wolf_context_t *context);
int add_floor_p(char **warray, wolf_context_t *context);

int handle_builtins(char **warray, wolf_context_t *context);

int builtin_require(char **warray, wolf_context_t *context);
int check_if_texture_exists(char **warray, wolf_context_t *context, int *err);

int parse_ray_file(wolf_context_t *ray, const char *path);

#endif /* PARSER_WOLF_H */
