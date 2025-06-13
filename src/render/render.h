/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Header file for render.
*/
#ifndef RENDER_WOLF_H
    #define RENDER_WOLF_H

    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include "raycaster/framebuffer/font/wolf_font.h"

typedef struct player_s player_t;

/* Fuck CSFML */
typedef struct sfVector4i {
    int x;
    int y;
    int w;
    int h;
} sfVector4i_t;

typedef struct floor_dirs_s {
    float dir_x0;
    float dir_y0;
    float dir_x1;
    float dir_y1;
} floor_dirs_t;

typedef struct tex_info_s {
    sfImage *image;
    int width;
    int height;
} tex_info_t;

typedef struct floor_ctx_s {
    player_t *player;
    tex_info_t *tex;
    floor_dirs_t *dirs;
    int width;
    int height;
} floor_ctx_t;

typedef struct floor_step_s {
    float floor_x;
    float floor_y;
    float step_x;
    float step_y;
} floor_step_t;

typedef struct draw_sprite_param_s {
    int y_min;
    int y_max;
    int x_min;
    int x_max;
    double depth;
    int sprite_width;
    int sprite_height;
    int x_start;
    int y_start;
    sfVector2u img_size;
} draw_sprite_param_t;

typedef struct draw_pixel_ctx_s {
    player_t *player;
    draw_sprite_param_t param;
    sfImage *image;
    sfIntRect rect;
} draw_pixel_ctx_t;

typedef struct cast_ray_params_s {
    int rays;
    double depth;
    float start_angle;
    sfVector2f collision;
    wall_t wall;
} cast_ray_params_t;

typedef struct sfIntRect_text_s {
    sfIntRect rect;
    textures_t *text;
} sfIntRect_text_t;

sfColor blend_rgb332(sfColor dst, sfColor src, float alpha);
int project_stuff_on_screen(player_t *player, sfVector2f pos,
    int *screen_x_out, double *depth_out);

void clear_framebuffer(player_t *player);
void put_pixel(player_t *player, sfVector2i xy, sfColor color, sfVector2f df);
void draw_rect(player_t *player, sfVector4i_t xy, sfColor color, double depth);
void draw_circle(player_t *player, sfVector4i_t centerr, int chn,
    sfColor color);
void clear_framebuffer(player_t *player);
void draw_sprite(sfVector2f xdp, player_t *player, textures_t *target,
    sfIntRect rect);
void draw_sprite_cropped(sfVector2f xdp, player_t *player,
    textures_t *target, sfIntRect rect);
void draw_sprite_x_y_2d(sfVector2f pos, player_t *player,
    float scale, sfIntRect_text_t recttext);

void draw_blacksheep(wolf_context_t *context, player_t *player);
void draw_bullets(wolf_context_t *context, player_t *player);
void draw_stuffs(wolf_context_t *context, player_t *player);
void draw_mob(wolf_context_t *data, player_t *player);
void draw_bsps(wolf_context_t *context, player_t *player);
void draw_heals(wolf_context_t *context, player_t *player);

void render_floor(player_t *p, sfVector2i screen, wolf_context_t *ctx);
void render_ceiling(player_t *player, sfVector2i screen, wolf_context_t *ctx);

void draw_wall(wolf_context_t *ray, player_t *player, cast_ray_params_t param);

typedef struct raycaster_param_s {
    int rays;
    sfVector2f base_pos;
    sfVector2f target_pos;
    int i;
} raycaster_param_t;

void cast_ray(wolf_context_t *ray, player_t *player, float angle,
    raycaster_param_t p);
void raycaster(wolf_context_t *context, player_t *player);

void draw_cursor(player_t *player);
void draw_hps(player_t *player);
void draw_ammo(player_t *player);
void draw_skill(player_t *player);
void draw_blacksheep_ui(player_t *player, wolf_context_t *context);
void draw_ui(wolf_context_t *context, player_t *player);
void draw_directions(wolf_context_t *context, player_t *player);

void player_render(wolf_context_t *context, player_t *player);
void player_render_draw(wolf_context_t *context);

// multithread
void multithread_render(wolf_context_t *context);
void destroy_render_multithread(wolf_context_t *context);
char init_render_multithread(wolf_context_t *context);

#endif /* RENDER_WOLF_H */
