/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for the wolf3d project.
*/
#ifndef MAP_WOLF_3D_H
    #define MAP_WOLF_3D_H
    #include <SFML/System.h>

typedef struct wall_s wall_t;
typedef struct bullet_s bullet_t;

typedef enum spawn_type_e {
    DEF,
    ATK,
    HIL,
} spawn_type_t;

typedef struct spawns_s {
    sfVector2f a;
    sfVector2f b;
    spawn_type_t type;
    struct spawns_s *next;
} spawns_t;

void delete_spawns(spawns_t *head);
spawns_t *find_spawn_point(spawns_t *head, spawn_type_t type);
int add_spawn_point(spawns_t **head, sfVector2f a, sfVector2f b,
    spawn_type_t type);

typedef struct bsp_s {
    sfVector2f a;
    sfVector2f b;
    sfVector2f center;
    struct bsp_s *next;
} bsp_t;

sfBool is_in_bsp(player_t *player, bsp_t *bsps);
int add_bsp(bsp_t **head, sfVector2f a, sfVector2f b);
void delete_bsp(bsp_t *head);

typedef struct heals_s {
    sfVector2f pos;
    long double is_taken;
    struct heals_s *next;
} heals_t;

int add_heal_point(heals_t **head, sfVector2f pos);
void delete_heals(heals_t *head);

typedef struct temp_wall_s {
    int index;
    wall_t wall;
    struct temp_wall_s *next;
} temp_wall_t;

void add_temp_wall(temp_wall_t **head, int i, wall_t wall);
void destoy_temp_walls(temp_wall_t *head);
void resolve_others_temp_wall_index(temp_wall_t *head, const int index);

typedef struct maps_s {
    char *name;
    int n_wall;
    wall_t *walls;
    bullet_t *bullets;
    stuffs_t *stuffs;
    spawns_t *spawns;
    bsp_t *bsp;
    heals_t *heals;
    textures_t *floor;
    textures_t *ceiling;
    temp_wall_t *temp_walls;
} maps_t;

maps_t *create_map(char *name);
void destroy_maps(maps_t **maps, const int nmap);

void remove_wall(wall_t **walls, int *count, int index, int dmg);
void remove_wall_at_index(wall_t **walls, int *count, int index);

#endif /* MAP_WOLF_3D_H */
