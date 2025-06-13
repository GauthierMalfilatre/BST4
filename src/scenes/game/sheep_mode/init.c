/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy bst scene.
*/
#include "wolf.h"
#include "../../../render/render.h"
#include "parser.h"

static int init_viewport(wolf_context_t *context, float scale)
{
    sfVector2f pos;

    for (int i = 0; i < context->n_players; i++) {
        sfRectangleShape_setScale(context->players[i]->utils->deadrect,
            (sfVector2f){scale, scale});
        sfSprite_setScale(context->players[i]->utils->render_sprite,
            (sfVector2f){scale, scale});
        pos.x = context->players[i]->param.offx ?
            context->view->win_size.x - 640 * scale : 0;
        if (context->n_players == 2)
            pos.y = (context->view->win_size.y / 2.f) - (480.f * scale / 2.f);
        else
            pos.y = context->players[i]->param.offy ?
                (context->view->win_size.y / 2.f) : 0;
        sfRectangleShape_setPosition(context->players[i]->utils->deadrect,
            (sfVector2f){pos.x, pos.y});
        sfSprite_setPosition(context->players[i]->utils->render_sprite,
            (sfVector2f){pos.x, pos.y});
    }
    return OK;
}

static int init_text(wolf_context_t *context)
{
    float r = context->view->win_size.y / 1080.f;
    sfFloatRect bounds;

    context->bst->font =
        sfFont_createFromFile("assets/fonts/Silkscreen-Regular.ttf");
    if (!context->bst->font)
        return ERROR;
    context->bst->text = sfText_create();
    if (!context->bst->text)
        return ERROR;
    sfText_setFont(context->bst->text, context->bst->font);
    sfText_setCharacterSize(context->bst->text, 20);
    sfText_setScale(context->bst->text, (sfVector2f){2.f * r, 2.f * r});
    sfText_setString(context->bst->text, "round 0:\n  00:00");
    bounds = sfText_getLocalBounds(context->bst->text);
    sfText_setOrigin(context->bst->text, (sfVector2f){
        bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f});
    sfText_setPosition(context->bst->text, (sfVector2f){
        context->view->win_size.x / 2.f, 100.f * r});
    return OK;
}

static int init_player(wolf_context_t *context)
{
    context->bst->clock = sfClock_create();
    context->bst->timelimit = 240.f;
    context->bst->scale_ratio = context->view->win_size.y / 1080.f;
    context->bst->score_rect = sfRectangleShape_create();
    context->bst->bar_rect = sfRectangleShape_create();
    return OK;
}

static void reinit_hps(heals_t *hps)
{
    for (heals_t *temp = hps; temp; temp = temp->next) {
        temp->is_taken = 0.f;
    }
}

int bst_init(wolf_context_t *context)
{
    if (!context)
        return ERROR;
    context->bst = calloc(1, sizeof(bst_t));
    context->bst->is_temp_wall = sfTrue;
    for (temp_wall_t *temp = context->cmap->temp_walls; temp; temp = temp->next) {
        add_wall(temp->wall, context->cmap);
        temp->index = context->cmap->n_wall - 1;
    }
    if (!context->bst || init_viewport(context, (context->view->win_size.y) /
        960.f) != OK)
        return ERROR;
    if (init_player(context) != OK)
        return ERROR;
    if (!context->bst->score_rect || !context->bst->bar_rect)
        return ERROR;
    reinit_hps(context->cmap->heals);    
    if (init_text(context) != OK)
        return ERROR;
    if (init_render_multithread(context) != OK)
        return ERROR;
    context->bst->rain = (rain_t *) 0;
    return OK;
}
