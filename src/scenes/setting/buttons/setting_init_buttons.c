/*
** EPITECH PROJECT, 2024
** buttons_init
** File description:
** initialize all buttons
*/

#include "setting_buttons.h"

static const char *get_button_string(unsigned int i, setting_t *setting)
{
    static char buffer[128];

    if (i <= B_SENSIBILITE) {
        snprintf(buffer, sizeof(buffer), "%s%d%s",
            text_help[i], setting->setting[i], text_qualifer[i]);
    } else if (i == B_FULLSCREEN) {
        snprintf(buffer, sizeof(buffer), "%s%s", text_help[i],
        setting->setting[SETTING_FULLSCREEN] ? "On" : "Off");
    } else
        return text_help[i];
    return buffer;
}

static sfText *create_button_text(unsigned int i, sfVector2f position,
    setting_t *setting)
{
    sfText *text = sfText_create();
    float height;

    if (!text)
        return NULL;
    sfText_setFont(text, setting->font);
    sfText_setCharacterSize(text, setting->font_size);
    sfText_setString(text, get_button_string(i, setting));
    sfText_setColor(text, sfWhite);
    height = sfText_getGlobalBounds(text).height;
    sfText_setOrigin(text, (sfVector2f){0, height});
    sfText_setPosition(text, position);
    return text;
}

static button_t create_button(sfVector2f position, sfVector2f size,
    unsigned int i)
{
    button_t btn;

    btn.shape = sfRectangleShape_create();
    btn.is_hovered = 0;
    btn.is_pressed = 0;
    btn.is_select = 0;
    btn.color = sfColor_fromRGBA(139, 158, 183, 100);
    btn.button_fonc = b_fonctions[i];
    if (!btn.shape)
        perror("Error: Failed to create button shape");
    sfRectangleShape_setOrigin(btn.shape,
        (sfVector2f){size.x / 2.0f, size.y / 2.0f});
    sfRectangleShape_setSize(btn.shape, size);
    sfRectangleShape_setFillColor(btn.shape,
        sfColor_fromRGBA(139, 158, 183, 100));
    sfRectangleShape_setPosition(btn.shape, position);
    btn.text = NULL;
    return btn;
}

void init_setting_buttons(wolf_context_t *window)
{
    unsigned int pos_width = window->view->win_size.x / 2;
    unsigned int pos_height = window->view->win_size.y / 2;
    sfVector2f position;
    sfVector2f size = {window->view->win_size.x * 0.8f,
        window->view->win_size.y * 0.07f};

    window->setting->buttons = malloc(sizeof(button_t) * nb_buttons_count);
    if (!window->setting->buttons)
        return;
    for (unsigned int i = 0; i < B_BACK; i++) {
        position = (sfVector2f){pos_width,
            (size.y * i) + (i * 15) + (pos_height - size.y)};
        window->setting->buttons[i] = create_button(position, size, i);
        position.x -= (size.x / 2.0f);
        window->setting->buttons[i].text =
        create_button_text(i, position, window->setting);
    }
}

static button_t create_setting_button(sfVector2f size, sfVector2f position,
    unsigned int btn_index)
{
    button_t button;

    button.shape = sfRectangleShape_create();
    if (!button.shape) {
        perror("Error: Failed to create button shape");
        return (button_t){0};
    }
    button.is_hovered = 0;
    button.is_pressed = 0;
    button.is_select = 0;
    button.button_fonc = b_fonctions[btn_index];
    button.color = sfTransparent;
    button.text = NULL;
    sfRectangleShape_setOrigin(button.shape, (sfVector2f){0, 0});
    sfRectangleShape_setSize(button.shape, size);
    sfRectangleShape_setFillColor(button.shape, button.color);
    sfRectangleShape_setPosition(button.shape, position);
    return button;
}

void create_bottom_buttons(wolf_context_t *window)
{
    sfVector2f size = {window->view->win_size.x * 0.07f,
        window->view->win_size.y * 0.07f};
    sfVector2f back_pos = {5, window->view->win_size.y - size.y - 5};
    sfVector2f apply_pos = {window->view->win_size.x - size.x - 10,
        window->view->win_size.y - size.y - 5};
    sfVector2f text_pos = {back_pos.x + 10, back_pos.y + size.y / 2};

    window->setting->buttons[B_BACK] =
    create_setting_button(size, back_pos, B_BACK);
    window->setting->buttons[B_BACK].text =
    create_button_text(B_BACK, text_pos, window->setting);
    text_pos = (sfVector2f){apply_pos.x + 5, apply_pos.y + size.y / 2};
    window->setting->buttons[B_APPLY] =
    create_setting_button(size, apply_pos, B_APPLY);
    window->setting->buttons[B_APPLY].text =
    create_button_text(B_APPLY, text_pos, window->setting);
}
