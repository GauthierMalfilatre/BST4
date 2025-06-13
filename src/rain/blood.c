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

void add_n_blood_drops(blood_t **head, const int n, sfVector2f pos)
{
    for (int i = 0; i < n; i++) {
        add_blood(head, pos);
    }
    return;
}

void destroy_blood_list(blood_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        destroy_blood_list(head->next);
    }
    free(head);
    return;
}

void add_blood(blood_t **head, sfVector2f pos)
{
    blood_t *new = malloc(sizeof(blood_t));

    if (!new)
        return;
    new->x = pos.x;
    new->y = pos.y;
    new->z = 240;
    new->depth = BMIN_DEPTH + ((float)(rand() % 1000) / 100.0f) *
        (BMAX_DEPTH - BMIN_DEPTH);
    new->velocity = BMIN_VELOCITY + ((float)(rand() % 1000) / 100.0f) *
        (BMAX_VELOCITY - BMIN_VELOCITY);
    new->next = *head;
    *head = new;
}

static void remove_blood_drop(blood_t **head, blood_t *tmp,
    blood_t *prev, blood_t *next)
{
    if (prev)
        prev->next = next;
    else
        *head = next;
    free(tmp);
}

void update_blood(blood_t **head, player_t *player)
{
    blood_t *tmp = *head;
    blood_t *prev = NULL;
    blood_t *next;
    float dt = player->delta_t / 50.f;

    for (; tmp; tmp = next) {
        next = tmp->next;
        tmp->x += tmp->depth * dt;
        tmp->z -= tmp->velocity * dt;
        tmp->velocity -= GRAVITY * dt;
        if (tmp->z > 300) {
            remove_blood_drop(head, tmp, prev, next);
            continue;
        }
        prev = tmp;
    }
}

void render_blood(blood_t **head, player_t *src)
{
    int radius = 2;
    double depth_out;
    int screen_out;

    for (blood_t *temp = *head; temp; temp = temp->next) {
        if (project_stuff_on_screen(src, (sfVector2f){temp->x, temp->y},
            &screen_out, &depth_out)) {
            draw_circle(src, (sfVector4i_t){screen_out, temp->z,
                radius, 0}, depth_out, sfRed);
        }
    }
}
