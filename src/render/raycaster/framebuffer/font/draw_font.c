/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Font file
*/
#include "wolf.h"
#include "wolf_font.h"

const draw_char_func_t letters[26] = {
    draw_letter_a, draw_letter_b, draw_letter_c, draw_letter_d, draw_letter_e,
    draw_letter_f, draw_letter_g, draw_letter_h, draw_letter_i, draw_letter_j,
    draw_letter_k, draw_letter_l, draw_letter_m, draw_letter_n, draw_letter_o,
    draw_letter_p, draw_letter_q, draw_letter_r, draw_letter_s, draw_letter_t,
    draw_letter_u, draw_letter_v, draw_letter_w, draw_letter_x, draw_letter_y,
    draw_letter_z
};

const draw_char_func_t numbers[10] = {
    draw_number_0, draw_number_1, draw_number_2, draw_number_3, draw_number_4,
    draw_number_5, draw_number_6, draw_number_7, draw_number_8, draw_number_9
};

void draw_text(player_t *player, char *text, sfVector4i_t xy_scale_ch,
    sfColor color)
{
    int x = xy_scale_ch.x;
    int y = xy_scale_ch.y;
    int pos_x = x;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] += ('a' - 'A');
        if (text[i] >= 'a' && text[i] <= 'z')
            letters[text[i] - 'a'](player, (sfVector2i){pos_x, y},
                (sfVector2i){xy_scale_ch.w, xy_scale_ch.h}, color);
        if (text[i] >= '0' && text[i] <= '9')
            numbers[text[i] - '0'](player, (sfVector2i){pos_x, y},
                (sfVector2i){xy_scale_ch.w, xy_scale_ch.h}, color);
        if (text[i] == '.')
            draw_point(player, (sfVector2i){pos_x, y},
                (sfVector2i){xy_scale_ch.w, xy_scale_ch.h}, color);            
        pos_x += xy_scale_ch.w * (text[i] != '.' ? 5 : 2);
    }
}
