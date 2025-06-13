/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy bst scene.
*/
#include "wolf.h"
#include "../../render/render.h"
#include "../selection/selection.h"

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

static void draw_winner(interlude_t *s, wolf_context_t *context)
{
    char bffer[512];
    view_t *v = context->view;
    float r = v->win_size.y / 1080.f;

    sprintf(bffer, "%s WON THE %s", context->team_winner ?
        "DEFENDERS" : "ATTACKERS", (context->wins.x >= 6 ||
        context->wins.y >= 6) ? "MATCH" : "ROUND");
    update_text(s->text, bffer);
    sfText_setOrigin(s->text, (sfVector2f){my_strlen(bffer) * 20 / 2, 20 / 2});
    sfText_setScale(s->text, (sfVector2f){2.f * r, 2.f * r});
    sfText_setPosition(s->text, (sfVector2f)
        {v->win_size.x / 2, 150 * r});
    sfRenderWindow_drawText(v->window, s->text, 0);
    return;
}

static void draw_player(interlude_t *s, wolf_context_t *context,
    player_t *player, int i)
{
    float r = context->view->win_size.y / 1080.f;
    char bffer[512];
    sfVector2f pos = (sfVector2f)
        {context->view->win_size.x / 2, (500 + i * 100.f + 50.f) * r};

    sprintf(bffer, "%-10s %3d %3d %8d", player->name, player->kd.x,
        player->kd.y, player->score);
    sfText_setOrigin(s->text, (sfVector2f){my_strlen(bffer) * 20 / 2, 20 / 2});
    sfRectangleShape_setPosition(s->rect, pos);
    sfRectangleShape_setFillColor(s->rect, team_colors[player->equipe]);
    sfRenderWindow_drawRectangleShape(context->view->window, s->rect, 0);
    sfText_setPosition(s->text, (sfVector2f){pos.x + 10 * r, pos.y + 20 * r});
    sfText_setString(s->text, bffer);
    sfText_setScale(s->text, (sfVector2f){1.5f * r, 1.5f * r});
    sfRenderWindow_drawText(context->view->window, s->text, 0);
}

static void draw_players(interlude_t *s, wolf_context_t *context)
{
    player_t **players = malloc(sizeof(player_t *) * context->n_players);
    float r = context->view->win_size.y / 1080.f;
    char bffer[512];

    sprintf(bffer, "%-10.10s %3.3s %3.3s %8.8s", "Player", "K", "D", "Score");
    sfText_setOrigin(s->text, (sfVector2f){my_strlen(bffer) * 20 / 2, 20 / 2});
    sfText_setPosition(s->text, (sfVector2f){context->view->win_size.x / 2 +
        10 * r, 450 * r});
    sfText_setString(s->text, bffer);
    sfText_setScale(s->text, (sfVector2f){1.5f * r, 1.5f * r});
    sfRenderWindow_drawText(context->view->window, s->text, 0);
    memcpy(players, context->players, sizeof(player_t *) * context->n_players);
    sort_list(players, context->n_players);
    sfRectangleShape_setSize(s->rect, (sfVector2f){800.f * r, 100.f * r});
    sfRectangleShape_setOrigin(s->rect, (sfVector2f){400.f * r, 20.f * r});
    for (int i = 0; i < context->n_players; i++) {
        draw_player(s, context, players[i], i);
    }
    free(players);
}

void draw_point_sub1(interlude_t *s, wolf_context_t *context, float r,
    float ry)
{
    char bffer[16];

    sfRectangleShape_setOrigin(s->rect, (sfVector2f){0, 0});
    sfRectangleShape_setSize(s->rect, (sfVector2f){600 * r, 100 * r});
    sfText_setScale(s->text, (sfVector2f){1.5f * r, 1.5f * r});
    sprintf(bffer, "%-2.2d\n", context->wins.x);
    sfText_setString(s->text, bffer);
    sfText_setOrigin(s->text, (sfVector2f){my_strlen(bffer) * 20 / 2, 0});
    sfRectangleShape_setPosition(s->rect, (sfVector2f){0, 300.f * ry});
    sfText_setPosition(s->text, (sfVector2f){500 * r, 320.f * ry});
    sfRectangleShape_setFillColor(s->rect, team_colors[0]);
    sfRenderWindow_drawRectangleShape(context->view->window, s->rect, 0);
    sfRenderWindow_drawText(context->view->window, s->text, 0);
}

void draw_point_sub2(interlude_t *s, wolf_context_t *context, float r,
    float ry)
{
    char bffer[16];

    sprintf(bffer, "%2.2d\n", context->wins.y);
    sfText_setString(s->text, bffer);
    sfText_setOrigin(s->text, (sfVector2f){my_strlen(bffer) * 20 / 2, 0});
    sfRectangleShape_setPosition(s->rect, (sfVector2f){(1920 - 600) * r,
        300 * ry});
    sfText_setPosition(s->text, (sfVector2f){(1920 * r - 500 * r),
        320.f * ry});
    sfRectangleShape_setFillColor(s->rect, team_colors[1]);
    sfRenderWindow_drawRectangleShape(context->view->window, s->rect, 0);
    sfRenderWindow_drawText(context->view->window, s->text, 0);
}

static void draw_points(interlude_t *s, wolf_context_t *context)
{
    float r = context->view->win_size.x / 1920.f;
    float ry = context->view->win_size.y / 1080.f;

    draw_point_sub1(s, context, r, ry);
    draw_point_sub2(s, context, r, ry);
}

void draw_two_texts_bottom(interlude_t *s, wolf_context_t *context,
    const char *left_text, const char *right_text)
{
    float r = context->view->win_size.y / 1080.f;
    sfVector2u win_size = context->view->win_size;
    sfFloatRect rect;

    sfText_setString(s->text, left_text);
    sfText_setScale(s->text, (sfVector2f){1.0f * r, 1.0f * r});
    sfText_setOrigin(s->text, (sfVector2f){0, 0});
    sfText_setPosition(s->text, (sfVector2f){10 * r, win_size.y - 40 * r});
    sfRenderWindow_drawText(context->view->window, s->text, NULL);
    sfText_setString(s->text, right_text);
    rect = sfText_getLocalBounds(s->text);
    sfText_setOrigin(s->text, (sfVector2f){rect.width, 0});
    sfText_setPosition(s->text, (sfVector2f){win_size.x - 10 * r,
        win_size.y - 40 * r});
    sfRenderWindow_drawText(context->view->window, s->text, NULL);
}

void interlude_draw(wolf_context_t *context)
{
    interlude_t *s;

    if (!context)
        return;
    s = context->interlude;
    sfRenderWindow_clear(context->view->window, sfColor_fromRGB(80, 80, 80));
    sfRenderWindow_drawSprite(context->view->window, s->sprite, NULL);
    draw_winner(s, context);
    if (context->mode == BS_GO) {
        draw_points(s, context);
    }
    draw_players(s, context);
    draw_two_texts_bottom(s, context,
        "PRESS space or X to quit", "PRESSE enter or A to continue");
}
