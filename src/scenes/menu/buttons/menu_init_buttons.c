/*
** EPITECH PROJECT, 2024
** buttons_init
** File description:
** initialize all buttons
*/

#include "menu_buttons.h"

static sfText *create_button_text(unsigned int i, menu_t *menu)
{
    sfText *text = sfText_create();
    sfFloatRect bounds;

    if (!text)
        return NULL;
    sfText_setFont(text, menu->font);
    sfText_setCharacterSize(text, menu->font_size);
    sfText_setString(text, text_help[i]);
    sfText_setColor(text, sfWhite);
    bounds = sfText_getLocalBounds(text);
    sfText_setOrigin(text, (sfVector2f){bounds.width / 2, bounds.height});
    sfText_setPosition(text,
        sfRectangleShape_getPosition(menu->buttons[i].shape));
    return text;
}

static button_t create_button(sfVector2f position, sfVector2f size,
    unsigned int i)
{
    button_t btn;

    btn.shape = sfRectangleShape_create();
    btn.default_size = size;
    btn.is_hovered = 0;
    btn.is_pressed = 0;
    btn.is_select = 0;
    btn.button_fonc = b_fonctions[i];
    if (!btn.shape)
        perror("Error: Failed to create button shape");
    sfRectangleShape_setOrigin(btn.shape,
        (sfVector2f){size.x / 2.0f, size.y / 2.0f});
    sfRectangleShape_setSize(btn.shape, size);
    sfRectangleShape_setFillColor(btn.shape,
        sfColor_fromRGBA(139, 158, 183, 200));
    sfRectangleShape_setPosition(btn.shape, position);
    btn.text = NULL;
    return btn;
}

void init_menu_buttons(wolf_context_t *window)
{
    unsigned int size = window->view->win_size.y * 0.07f;
    unsigned int pos_width = window->view->win_size.x / 2;
    unsigned int pos_height = window->view->win_size.y / 2;
    sfVector2f position;

    window->menu->buttons = malloc(sizeof(button_t) * nb_buttons_count);
    if (!window->menu->buttons)
        return;
    for (int i = 0; i < nb_buttons_count; i++) {
        position = (sfVector2f){pos_width, (size * i) +
            (i * 40) + (pos_height - size)};
        window->menu->buttons[i] = create_button(
            position,
            (sfVector2f){size * 3, size},
            i);
        window->menu->buttons[i].text =
        create_button_text(i, window->menu);
    }
}
