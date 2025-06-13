/*
** EPITECH PROJECT, 2024
** mouse
** File description:
** mouse utils
*/

#include "wolf.h"

char is_mouse_over_button(const sfRectangleShape *button,
    sfVector2f mouse_pos)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(button);

    return sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y);
}
