/*
** EPITECH PROJECT, 2025
** MY_WOLRD
** File description:
** Render menu scene
*/
#include "wolf.h"
#include "utils.h"

void draw_string(sfRenderWindow *window, char *str, sfVector2f pos,
    sfVector2f size)
{
    sfFont *font = sfFont_createFromFile(
        "./assets/fonts/Silkscreen-Regular.ttf");
    sfText *text = sfText_create();

    if (!font)
        return;
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setPosition(text, pos);
    sfText_setScale(text, size);
    sfRenderWindow_drawText(window, text, sfFalse);
    sfFont_destroy(font);
    sfText_destroy(text);
    return;
}
