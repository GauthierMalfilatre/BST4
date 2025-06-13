/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy bst scene.
*/
#include "wolf.h"
#include "../../render/render.h"

#include "wolf.h"
#include "../../render/render.h"

static int init_bg(wolf_context_t *context)
{
    sfTexture *texture = get_texture(context->textures, "__interbg") ?
        get_texture(context->textures, "__interbg")->texture : NULL;
    sfVector2f scale;

    if (!texture) {
        interlude_destroy(context);
        return ERROR;
    }
    context->interlude->sprite = sfSprite_create();
    if (!context->interlude->sprite) {
        interlude_destroy(context);
        return ERROR;
    }
    sfSprite_setTexture(context->interlude->sprite, texture, sfTrue);
    scale = (sfVector2f){
        context->view->win_size.x / 640.f,
        context->view->win_size.y / 480.f
    };
    sfSprite_setScale(context->interlude->sprite, scale);
    return OK;
}

static int init_text(wolf_context_t *context)
{
    interlude_t *interlude = context->interlude;

    interlude->text = sfText_create();
    if (!interlude->text)
        return ERROR;
    interlude->font =
        sfFont_createFromFile("assets/fonts/Silkscreen-Regular.ttf");
    if (!interlude->font)
        return ERROR;
    sfText_setFont(interlude->text, interlude->font);
    interlude->rect = sfRectangleShape_create();
    if (!interlude->rect)
        return ERROR;
    interlude->clock = sfClock_create();
    if (!interlude->clock)
        return ERROR;
    return OK;
}

int interlude_init(wolf_context_t *context)
{
    if (!context)
        return ERROR;
    context->interlude = malloc(sizeof(interlude_t));
    if (!context->interlude)
        return ERROR;
    memset(context->interlude, 0, sizeof(interlude_t));
    if (init_bg(context) != OK)
        return ERROR;
    if (init_text(context) != OK) {
        interlude_destroy(context);
        return ERROR;
    }
    return OK;
}
