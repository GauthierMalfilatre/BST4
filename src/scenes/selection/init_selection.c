/*
** EPITECH PROJECT, 2024
** setting wolf3d
** File description:
** setting wolf3d
*/

#include "selection.h"

void init_selection_background(wolf_context_t *window)
{
    sfVector2u tex_size;
    float scale_x;
    float scale_y;

    window->selection->background_menu = sfSprite_create();
    window->selection->texture_bg_menu =
    sfTexture_createFromFile("./assets/menu_assets/menu_background_2.png", 0);
    sfSprite_setTexture(window->selection->background_menu,
        window->selection->texture_bg_menu, sfTrue);
    tex_size = sfTexture_getSize(window->selection->texture_bg_menu);
    scale_x = (float)window->view->win_size.x / (float)tex_size.x;
    scale_y = (float)window->view->win_size.y / (float)tex_size.y;
    sfSprite_setScale(window->selection->background_menu,
        (sfVector2f){scale_x, scale_y});
}

void init_selection_text(wolf_context_t *window)
{
    sfFloatRect bounds;
    sfText *text;

    window->selection->font =
    sfFont_createFromFile("./assets/fonts/Silkscreen-Regular.ttf");
    window->selection->font_size = (0.015f * window->view->window_diagonal);
    text = sfText_create();
    sfText_setString(text, "Select Player and map");
    sfText_setFont(text, window->selection->font);
    sfText_setColor(text, sfWhite);
    sfText_setCharacterSize(text, window->selection->font_size * 2);
    bounds = sfText_getLocalBounds(text);
    sfText_setOrigin(text, (sfVector2f){bounds.width / 2, bounds.height});
    sfText_setPosition(text,
        (sfVector2f){window->view->win_size.x / 2,
            window->view->win_size.y * 0.05f});
    window->selection->text_selection = text;
}

static void init_text_selection_map(wolf_context_t *window, sfVector2f size,
    sfVector2f position)
{
    sfFloatRect bounds;

    window->selection->text_map = sfText_create();
    if (!window->selection->text_map)
        return;
    sfText_setFont(window->selection->text_map, window->selection->font);
    sfText_setCharacterSize(window->selection->text_map,
        window->selection->font_size);
    sfText_setString(window->selection->text_map, window->maps[0]->name);
    sfText_setColor(window->selection->text_map, sfWhite);
    bounds = sfText_getLocalBounds(window->selection->text_map);
    sfText_setOrigin(window->selection->text_map,
        (sfVector2f){bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f});
    sfText_setPosition(window->selection->text_map,
        (sfVector2f){position.x + size.x / 2.0f, position.y + size.y / 2.0f});
}

void init_selection_map(wolf_context_t *window)
{
    sfVector2u win_size = window->view->win_size;
    sfVector2f size = {win_size.x * 0.25f, win_size.y * 0.10f};
    sfVector2f position = {(win_size.x - size.x) / 2.0f, win_size.y * 0.8f};

    window->selection->rect_map = sfRectangleShape_create();
    if (!window->selection->rect_map) {
        perror("Erreur : échec de création du rectangle de map");
        return;
    }
    sfRectangleShape_setSize(window->selection->rect_map, size);
    sfRectangleShape_setPosition(window->selection->rect_map, position);
    sfRectangleShape_setFillColor(window->selection->rect_map,
        sfColor_fromRGBA(80, 80, 80, 200));
    sfRectangleShape_setOutlineColor(window->selection->rect_map, sfWhite);
    sfRectangleShape_setOutlineThickness(window->selection->rect_map, 2.0f);
    init_text_selection_map(window, size, position);
    window->wins = (sfVector2i){0, 0};
}
