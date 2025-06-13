/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for the wolf3d project.
*/
#include "wolf.h"
#include "scenes.h"
#include "rain.h"
#include "../render/render.h"

void add_n_rain_drops(rain_t **head, const int n)
{
    for (int i = 0; i < n; i++) {
        add_rain(head);
    }
    return;
}

void add_rain(rain_t **head)
{
    rain_t *new_drop = malloc(sizeof(rain_t));
    float df;

    if (!new_drop)
        return;
    new_drop->x = rand() % 640;
    new_drop->y = -1 * (rand() % 480);
    new_drop->depth = MIN_DEPTH + ((float)(rand() % 30)) *
        (MAX_DEPTH - MIN_DEPTH);
    df = 1.0f - new_drop->depth;
    new_drop->velocity = MIN_VELOCITY + df * (MAX_VELOCITY - MIN_VELOCITY);
    new_drop->next = *head;
    *head = new_drop;
    return;
}

void destroy_rain_list(rain_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        destroy_rain_list(head->next);
    }
    free(head);
    return;
}

void draw_rain_drops(rain_t *head, player_t *player, float delta_t)
{
    sfColor color;
    sfVector4i_t xy;
    float size_factor;
    int width;
    int height;

    for (rain_t *temp = head; temp; temp = temp->next) {
        temp->y += temp->velocity * delta_t;
        if (temp->y > 480.f)
            temp->y = -1 * (rand() % 480);
        size_factor = 1.0f - temp->depth;
        width = 1 + (int)(size_factor * 2);
        height = 6 + (int)(size_factor * 10);
        xy = (sfVector4i_t){(int)temp->x, (int)temp->y, width, height};
        color = sfColor_fromRGBA(150, 150, 255, 180);
        if (player)
            draw_rect(player, xy, color, SELF_CHN);
    }
}
