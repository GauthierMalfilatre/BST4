/*
** EPITECH PROJECT, 2024
** My_world
** File description:
** my_world
*/

#include "menu.h"

void init_menu_background(wolf_context_t *window)
{
    sfVector2u tex_size;
    float scale_x;
    float scale_y;

    window->menu->background_menu = sfSprite_create();
    window->menu->texture_bg_menu =
    sfTexture_createFromFile("./assets/menu_assets/menu_background_2.png", 0);
    sfSprite_setTexture(window->menu->background_menu,
        window->menu->texture_bg_menu, sfTrue);
    tex_size = sfTexture_getSize(window->menu->texture_bg_menu);
    scale_x = (float)window->view->win_size.x / (float)tex_size.x;
    scale_y = (float)window->view->win_size.y / (float)tex_size.y;
    sfSprite_setScale(window->menu->background_menu,
        (sfVector2f){scale_x, scale_y});
}

void init_menu_text(wolf_context_t *window)
{
    sfFloatRect bounds;
    sfText *text;

    window->menu->font =
    sfFont_createFromFile("./assets/fonts/Silkscreen-Regular.ttf");
    window->menu->font_size = (0.015f * window->view->window_diagonal);
    text = sfText_create();
    sfText_setString(text, "\t\t\tFeeria Chronicles:\n"
        "Black Sheep tournament 4th edition");
    sfText_setFont(text, window->menu->font);
    sfText_setColor(text, sfWhite);
    sfText_setCharacterSize(text, window->menu->font_size * 2);
    bounds = sfText_getLocalBounds(text);
    sfText_setOrigin(text, (sfVector2f){bounds.width / 2, bounds.height});
    sfText_setPosition(text,
        (sfVector2f){window->view->win_size.x / 2,
            window->view->win_size.y * 0.2});
    window->menu->text_menu = text;
}
