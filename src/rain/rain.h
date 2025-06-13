/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for the wolf3d project.
*/
#ifndef RAIN_WOLF_3D_H
    #define RAIN_WOLF_3D_H
    #define BMIN_DEPTH -1.f
    #define BMAX_DEPTH 1.f
    #define MIN_DEPTH 0.1f
    #define MAX_DEPTH 1.0f
    #define MIN_VELOCITY 10.0f
    #define MAX_VELOCITY 20.0f
    #define BMIN_VELOCITY 5.0f
    #define BMAX_VELOCITY 10.0f
    #define GRAVITY 9.8f
    #include "wolf.h"

typedef struct rain_s {
    float x;
    float y;
    float velocity;
    float depth;
    struct rain_s *next;
} rain_t;

typedef struct blood_s {
    float x;
    float y;
    float z;
    float velocity;
    float depth;
    struct blood_s *next;
} blood_t;

void destroy_rain_list(rain_t *head);
void add_n_rain_drops(rain_t **head, const int n);
void add_rain(rain_t **head);
void draw_rain_drops(rain_t *head, player_t *player, float delta_t);

void add_blood(blood_t **head, sfVector2f pos);
void add_n_blood_drops(blood_t **head, const int n, sfVector2f pos);
void destroy_blood_list(blood_t *head);
void update_blood(blood_t **head, player_t *player);
void render_blood(blood_t **head, player_t *src);

#endif
