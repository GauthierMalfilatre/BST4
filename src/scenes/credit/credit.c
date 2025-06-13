/*
** EPITECH PROJECT, 2024
** credit
** File description:
** credit
*/

#include "scenes.h"
#include "credit.h"

int credit_init(wolf_context_t *window)
{
    window->credit = malloc(sizeof(credit_t));
    if (!window->credit)
        return ERROR;
    init_credit_background(window);
    init_credit_text(window);
    return OK;
}

void credit_update(wolf_context_t *window)
{
    (void)window;
    return;
}

void credit_event(wolf_context_t *window)
{
    if (window->evt.type == sfEvtClosed) {
        sfRenderWindow_close(window->view->window);
        return;
    }
    if (window->evt.type == sfEvtKeyPressed) {
        if (window->evt.key.code == sfKeyEscape ||
            window->evt.key.code == sfKeyEnter) {
            change_scene(MENU_SCENE, window);
        }
    }
}

void credit_draw(wolf_context_t *window)
{
    sfRenderWindow_clear(window->view->window, sfBlack);
    sfRenderWindow_drawSprite(window->view->window,
        window->credit->background_credit, NULL);
    sfRenderWindow_drawText(window->view->window,
        window->credit->text_credit, NULL);
}

void credit_destroy(wolf_context_t *window)
{
    if (!window->credit)
        return;
    if (window->credit->background_credit)
        sfSprite_destroy(window->credit->background_credit);
    if (window->credit->texture_bg_credit)
        sfTexture_destroy(window->credit->texture_bg_credit);
    sfFont_destroy(window->credit->font);
    sfText_destroy(window->credit->text_credit);
    free(window->credit);
}
