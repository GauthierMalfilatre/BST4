/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Font file
*/
#ifndef WOLF_FONT_H
    #define WOLF_FONT_H
    #include "../../../render.h"

typedef void (*draw_char_func_t)(player_t *player, sfVector2i xy,
    sfVector2i scale_ch, sfColor color);

void draw_letter_a(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_b(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_c(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_d(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_e(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_f(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_g(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_h(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_i(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_j(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_k(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_l(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_m(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_n(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_o(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_p(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_q(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_r(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_s(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_t(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_u(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_v(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_w(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_x(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_y(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_letter_z(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);

void draw_number_0(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_1(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_2(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_3(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_4(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_5(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_6(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_7(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_8(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);
void draw_number_9(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);

void draw_point(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color);

void draw_text(player_t *player, char *text, sfVector4i_t xy_scale_ch,
    sfColor color);

#endif
