/*
** EPITECH PROJECT, 2024
** credit init
** File description:
** credit initialization
*/

#include "credit.h"

static long get_file_length(FILE *file)
{
    long length;

    if (!file || fseek(file, 0, SEEK_END) != 0)
        return -1;
    length = ftell(file);
    if (length < 0)
        return -1;
    rewind(file);
    return length;
}

static char *alloc_and_read(FILE *file, long length)
{
    char *buffer = malloc((size_t)length + 1);
    size_t read;

    if (!buffer)
        return NULL;
    read = fread(buffer, 1, (size_t)length, file);
    if ((long)read != length) {
        free(buffer);
        return NULL;
    }
    buffer[length] = '\0';
    return buffer;
}

static char *load_credits_text(const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    char *buffer = NULL;
    long length;

    if (!file)
        return NULL;
    length = get_file_length(file);
    if (length < 0) {
        fclose(file);
        return NULL;
    }
    buffer = alloc_and_read(file, length);
    fclose(file);
    return buffer;
}

void init_credit_background(wolf_context_t *window)
{
    sfVector2u tex_size;
    float scale_x;
    float scale_y;

    window->credit->background_credit = sfSprite_create();
    window->credit->texture_bg_credit =
    sfTexture_createFromFile("./assets/menu_assets/menu_background_2.png", 0);
    sfSprite_setTexture(window->credit->background_credit,
        window->credit->texture_bg_credit, sfTrue);
    tex_size = sfTexture_getSize(window->credit->texture_bg_credit);
    scale_x = (float)window->view->win_size.x / (float)tex_size.x;
    scale_y = (float)window->view->win_size.y / (float)tex_size.y;
    sfSprite_setScale(window->credit->background_credit,
        (sfVector2f){scale_x, scale_y});
}

void init_credit_text(wolf_context_t *window)
{
    char *text = load_credits_text("./assets/credit_assets/credit.txt");
    sfFloatRect bounds;

    window->credit->font =
        sfFont_createFromFile("./assets/fonts/Silkscreen-Regular.ttf");
    window->credit->font_size = (0.015f * window->view->window_diagonal);
    window->credit->text_credit = sfText_create();
    sfText_setString(window->credit->text_credit, text);
    sfText_setFont(window->credit->text_credit, window->credit->font);
    sfText_setColor(window->credit->text_credit, sfWhite);
    sfText_setCharacterSize(window->credit->text_credit,
        window->credit->font_size);
    bounds = sfText_getLocalBounds(window->credit->text_credit);
    sfText_setOrigin(window->credit->text_credit,
        (sfVector2f){bounds.width / 2, bounds.height / 2});
    sfText_setPosition(window->credit->text_credit,
        (sfVector2f){window->view->win_size.x / 2.0f,
            window->view->win_size.y / 2.0f});
    free(text);
}
