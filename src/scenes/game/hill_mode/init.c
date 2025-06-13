/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy hill scene.
*/
#include "wolf.h"
#include "../../../render/render.h"

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

    context->hill->font =
        sfFont_createFromFile("assets/fonts/Silkscreen-Regular.ttf");
    if (!context->hill->font)
        return ERROR;
    context->hill->text = sfText_create();
    if (!context->hill->text)
        return ERROR;
    sfText_setFont(context->hill->text, context->hill->font);
    sfText_setCharacterSize(context->hill->text, 20);
    sfText_setScale(context->hill->text, (sfVector2f){2.f * r, 2.f * r});
    sfText_setString(context->hill->text, "00:00");
    bounds = sfText_getLocalBounds(context->hill->text);
    sfText_setOrigin(context->hill->text, (sfVector2f){
        bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f});
    sfText_setPosition(context->hill->text, (sfVector2f){
        context->view->win_size.x / 2.f, 100.f * r});
    return OK;
}

static int init_player(wolf_context_t *context)
{
    context->hill->clock = sfClock_create();
    context->hill->timelimit = 600.f;
    context->hill->scale_ratio = context->view->win_size.y / 1080.f;
    context->hill->score_rect = sfRectangleShape_create();
    context->hill->bar_rect = sfRectangleShape_create();
    return OK;
}

int hill_init(wolf_context_t *context)
{
    if (!context)
        return ERROR;
    context->hill = calloc(1, sizeof(hill_t));
    if (!context->hill || init_viewport(context, (context->view->win_size.y) /
        960.f) != OK)
        return ERROR;
    if (init_player(context) != OK)
        return ERROR;
    if (!context->hill->score_rect || !context->hill->bar_rect)
        return ERROR;
    if (init_text(context) != OK)
        return ERROR;
    if (init_render_multithread(context) != OK)
        return ERROR;
    return OK;
}
