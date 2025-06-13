/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy hill scene.
*/
#include "wolf.h"
#include "../../../render/render.h"
#include "../../selection/selection.h"

static int find_x(player_t *player)
{
    sfSprite *sprite = player->utils->render_sprite;
    float sizex = player->param.size.x;
    float posx = sfSprite_getPosition(sprite).x;

    if (posx == 0.f)
        return sfSprite_getScale(sprite).x * sizex;
    else
        return posx - 10.f;
}

static void draw_rects(wolf_context_t *context)
{
    sfRectangleShape *rect = context->hill->bar_rect;
    int x;
    sfVector2f boh;

    for (int i = 0; i < context->n_players; i++) {
        x = find_x(context->players[i]);
        boh = (sfVector2f){
            x, context->n_players > 2 ? sfSprite_getPosition(
            context->players[i]->utils->render_sprite).y : 0
        };
        sfRectangleShape_setPosition(rect, boh);
        sfRectangleShape_setSize(rect, (sfVector2f){
            10, context->n_players < 3 ? 20000 :
            sfSprite_getScale(context->players[i]->utils->render_sprite).y *
            context->players[i]->param.size.y
        });
        sfRectangleShape_setFillColor(rect,
            team_colors[context->players[i]->equipe]);
        sfRenderWindow_drawRectangleShape(context->view->window, rect, 0);
    }
}

static void sort_list(player_t **players, const int n)
{
    int i = 0;
    player_t *temp;

    while (i < n - 1) {
        if (players[i]->score < players[i + 1]->score) {
            temp = players[i];
            players[i] = players[i + 1];
            players[i + 1] = temp;
            i = 0;
            continue;
        }
        i++;
    }
}

static void draw_score(wolf_context_t *context, sfRectangleShape *rect)
{
    char buffer[64];
    sfVector2f pos;
    float r = context->hill->scale_ratio;
    player_t **players = malloc(sizeof(player_t *) * context->n_players);

    memcpy(players, context->players, sizeof(player_t *) * context->n_players);
    sort_list(players, context->n_players);
    for (int i = 0; i < context->n_players; i++) {
        pos = (sfVector2f){(context->view->win_size.x / 2 -
            context->view->win_size.x * 0.1f), 200 * r + (40 * i) * r};
        sfRectangleShape_setPosition(rect, pos);
        sfRectangleShape_setSize(rect, (sfVector2f){context->view->win_size.x *
            0.2f, 45 * r});
        sfRectangleShape_setFillColor(rect, team_colors[players[i]->equipe]);
        sprintf(buffer, "%s %d\n", players[i]->name, players[i]->score);
        sfRenderWindow_drawRectangleShape(context->view->window, rect, 0);
        draw_string(context->view->window, buffer, pos, (sfVector2f){r, r});
    }
    free(players);
}

void hill_draw(wolf_context_t *context)
{
    char buffer[32];
    float timestamp = context->hill->timelimit -
        sfTime_asSeconds(sfClock_getElapsedTime(context->hill->clock));

    sfRenderWindow_clear(context->view->window, sfColor_fromRGB(50, 50, 50));
    sprintf(buffer, "%.2d:%.2d", (int)(timestamp / 60.f) % 60,
    (int)fmod(timestamp, 60));
    player_render_draw(context);
    draw_rects(context);
    draw_score(context, context->hill->score_rect);
    if (context->hill->text)
        sfText_setString(context->hill->text, buffer);
    sfRenderWindow_drawText(context->view->window, context->hill->text,
        sfFalse);
}
