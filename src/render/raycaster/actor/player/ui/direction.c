/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../../render.h"
#include "scenes.h"

static sfBool is_the_good_bsp(blacksheep_t *bs, bsp_t *bsp)
{
    return (bs->pos.x > bsp->a.x && bs->pos.x < bsp->b.x && bs->pos.y >
        bsp->a.y && bs->pos.y < bsp->b.y);
}

static void draw_point_bsp_ui(player_t *player, wolf_context_t *context, int i,
    int xout)
{
    char buffer[8];
    sfColor circle_color = !context->bs->is_fired ?
        sfColor_fromRGB(80, 80, 80) : sfYellow;

    sprintf(buffer, "%c", 'a' + i);
    draw_circle(player, (sfVector4i_t){xout + 4, 20, 20, 0}, UX_CHN,
        circle_color);
    draw_text(player, buffer, (sfVector4i_t){xout, 10, 4, UX_CHN},
        sfRed);
}

void draw_directions(wolf_context_t *context, player_t *player)
{
    int xout;
    double d_out;
    int i = 0;

    if (player->equipe == 0 && !context->bs->is_carried &&
        !context->bs->is_fired) {
        if (project_stuff_on_screen(player, context->bs->pos, &xout, &d_out)) {
            draw_sprite_x_y_2d((sfVector2f){xout - 64, -70}, player, 1.f,
                (sfIntRect_text_t){(sfIntRect){0, 0, 128, 128},
                get_texture(context->textures, "__bs")});
        }
    }
    for (bsp_t *temp = context->cmap->bsp; temp; temp = temp->next) {
        if ((!context->bs->is_fired || is_the_good_bsp(context->bs, temp))
            && project_stuff_on_screen(player, temp->center, &xout, &d_out)) {
            draw_point_bsp_ui(player, context, i, xout);
        }
        i++;
    }
}
