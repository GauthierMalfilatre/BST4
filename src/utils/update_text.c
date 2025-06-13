/*
** EPITECH PROJECT, 2024
** update text pos
** File description:
** reset text position
*/

#include "wolf.h"

void update_text_pos(sfRectangleShape *bouton, sfText *text)
{
    sfFloatRect bounds = sfText_getGlobalBounds(text);

    sfText_setOrigin(text, (sfVector2f){bounds.width / 2, bounds.height});
    sfText_setPosition(text, sfRectangleShape_getPosition(bouton));
}

void update_text(sfText *text, const char *str)
{
    sfFloatRect bounds;

    if (!text)
        return;
    sfText_setString(text, str);
    bounds = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){bounds.width / 2, bounds.height});
}
