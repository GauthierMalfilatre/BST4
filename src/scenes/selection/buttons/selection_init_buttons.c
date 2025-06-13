/*
** EPITECH PROJECT, 2024
** buttons_init
** File description:
** initialize all buttons
*/

#include "selection_buttons.h"

static sfText *create_centered_text(const char *str, sfVector2f center,
    selection_t *selection)
{
    sfText *text = sfText_create();
    sfFloatRect bounds;

    if (!text)
        return NULL;
    sfText_setFont(text, selection->font);
    sfText_setCharacterSize(text, selection->font_size);
    sfText_setString(text, str);
    sfText_setColor(text, sfWhite);
    bounds = sfText_getLocalBounds(text);
    sfText_setOrigin(text, (sfVector2f){
        bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f
    });
    sfText_setPosition(text, center);
    return text;
}

static void set_sprite_position(button_t *btn)
{
    sfVector2f size = sfRectangleShape_getSize(btn->shape);
    sfVector2f pos = sfRectangleShape_getPosition(btn->shape);
    sfVector2f origin = sfRectangleShape_getOrigin(btn->shape);
    sfVector2u tex_size = {82, 128};
    float scale = fmin(size.x / tex_size.x, size.y / tex_size.y);
    sfVector2f sprite_size = {tex_size.x * scale, tex_size.y * scale};

    sfSprite_setScale(btn->character, (sfVector2f){scale, scale});
    sfSprite_setPosition(btn->character, (sfVector2f){
        pos.x - origin.x + (size.x - sprite_size.x) / 2.0f,
        pos.y - origin.y + (size.y - sprite_size.y) / 2.0f
    });
}

static void init_button_sprite(button_t *btn, sfTexture *texture)
{
    if (!btn)
        return;
    btn->character = sfSprite_create();
    if (!btn->character) {
        perror("Failed to create sprite");
        return;
    }
    sfSprite_setTexture(btn->character, texture, sfFalse);
    set_sprite_position(btn);
}

static button_t create_button(sfVector2f position, sfVector2f size,
    sfVector2f orignin, sfColor color)
{
    button_t btn = {0};

    btn.shape = sfRectangleShape_create();
    if (!btn.shape) {
        perror("Error: Failed to create button shape");
        return (button_t){0};
    }
    btn.is_hovered = 0;
    btn.is_pressed = 0;
    btn.is_select = 0;
    btn.color = color;
    sfRectangleShape_setOrigin(btn.shape, orignin);
    sfRectangleShape_setSize(btn.shape, size);
    sfRectangleShape_setFillColor(btn.shape, color);
    sfRectangleShape_setPosition(btn.shape, position);
    return btn;
}

static sfColor getclr(wolf_context_t *w, int i)
{
    return team_colors[w->players[i]->equipe];
}

void init_selection_buttons(wolf_context_t *w)
{
    float cy = w->view->win_size.y * 0.4f;
    float b[2] = {w->view->win_size.x * 0.15f, w->view->win_size.y * 0.6f};
    float total_w = w->n_players * b[0] + (w->n_players - 1) * 15.0f;
    float start_x = w->view->win_size.x / 2.0f - total_w / 2.0f + b[0] / 2.0f;
    sfVector2f pos;
    sfVector2f pos_text;

    w->selection->buttons = calloc(w->n_players + 4, sizeof(button_t));
    if (!w->selection->buttons)
        return;
    for (int i = 0; i < w->n_players; i++) {
        pos = (sfVector2f){start_x + i * (b[0] + 15.0f), cy};
        w->selection->buttons[i] = create_button(pos, (sfVector2f)
        {b[0], b[1]}, (sfVector2f){b[0] / 2.0f, b[1] / 2.0f}, getclr(w, i));
        init_button_sprite(&w->selection->buttons[i],
            w->characters[0]->apparance->texture);
        pos_text = (sfVector2f){pos.x, pos.y + b[1] / 2.0f + b[1] * 0.05f};
        w->selection->buttons[i].text = create_centered_text(
            w->players[i]->name, pos_text, w->selection);
        w->selection->buttons[i].button_fonc = b_fonctions[RUMBLE_INDEX];
    }
}

void create_bottom_selection(wolf_context_t *w)
{
    sfVector2f size = {w->view->win_size.x * 0.07f,
        w->view->win_size.y * 0.07f};
    sfVector2f back_pos = {5, w->view->win_size.y - size.y - 5};
    sfVector2f start_pos = {w->view->win_size.x - size.x - 10,
        w->view->win_size.y - size.y - 5};
    unsigned int back_idx = BACK_INDEX + w->n_players;
    unsigned int start_idx = START_INDEX + w->n_players;

    w->selection->buttons[back_idx] = create_button(back_pos, size,
        (sfVector2f){0, 0}, sfTransparent);
    w->selection->buttons[start_idx] = create_button(start_pos, size,
        (sfVector2f){0, 0}, sfTransparent);
    w->selection->buttons[back_idx].text = create_centered_text("Back",
        (sfVector2f){back_pos.x + size.x / 2, back_pos.y + size.y / 2},
        w->selection);
    w->selection->buttons[start_idx].text = create_centered_text("Start",
        (sfVector2f){start_pos.x + size.x / 2, start_pos.y + size.y / 2},
        w->selection);
    w->selection->buttons[back_idx].button_fonc = b_fonctions[BACK_INDEX];
    w->selection->buttons[start_idx].button_fonc = b_fonctions[START_INDEX];
}

void create_arrow_buttons(wolf_context_t *w)
{
    sfVector2f rect_pos = sfRectangleShape_getPosition(w->selection->rect_map);
    sfVector2f rect_size = sfRectangleShape_getSize(w->selection->rect_map);
    sfVector2f arrow_size = {w->view->win_size.x * 0.04f, rect_size.y};
    sfVector2f left_pos = {rect_pos.x - arrow_size.x - 10.0f, rect_pos.y};
    sfVector2f right_pos = {rect_pos.x + rect_size.x + 10.0f, rect_pos.y};
    unsigned int left_idx = LEFT_INDEX + w->n_players;
    unsigned int right_idx = RIGHT_INDEX + w->n_players;

    w->selection->buttons[left_idx] = create_button(left_pos, arrow_size,
        (sfVector2f){0, 0}, sfColor_fromRGBA(100, 100, 255, 150));
    w->selection->buttons[right_idx] = create_button(right_pos, arrow_size,
        (sfVector2f){0, 0}, sfColor_fromRGBA(100, 100, 255, 150));
    w->selection->buttons[left_idx].text = create_centered_text("<",
        (sfVector2f){left_pos.x + arrow_size.x / 2,
            left_pos.y + arrow_size.y / 2}, w->selection);
    w->selection->buttons[right_idx].text = create_centered_text(">",
        (sfVector2f){right_pos.x + arrow_size.x / 2,
            right_pos.y + arrow_size.y / 2}, w->selection);
    w->selection->buttons[left_idx].button_fonc = b_fonctions[LEFT_INDEX];
    w->selection->buttons[right_idx].button_fonc = b_fonctions[RIGHT_INDEX];
}
