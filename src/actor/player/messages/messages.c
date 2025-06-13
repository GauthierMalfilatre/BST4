/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Create players.
*/
#include "wolf.h"
#include "math.h"

int add_message(messages_t **head, const float duration, char *text,
    const message_type_t type)
{
    messages_t *new = calloc(1, sizeof(messages_t));

    if (!new) {
        return ERROR;
    }
    new->duration = duration;
    new->text = strdup(text);
    new->prev = (messages_t *) 0;
    new->type = type;
    new->next = *head;
    if (*head) {
        (*head)->prev = new;
    }
    *head = new;
    return OK;
}

void delete_all_messages(messages_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        delete_all_messages(head->next);
    }
    free(head->text);
    free(head);
    return;
}

void delete_a_message(messages_t **head, messages_t *message)
{
    if (!message || !head || !*head)
    {
        return;
    }
    if (message->next) {
        message->next->prev = message->prev;
    }
    if (message->prev) {
        message->prev->next = message->next;
    } else {
        *head = message->next;
    }
    return;
}

void update_messages(player_t *player)
{
    messages_t *temp2 = (messages_t *) 0;

    for (messages_t *temp = player->messages; temp;) {
        temp->duration -= player->delta_t;
        if (temp->duration <= 0.f) {
            temp2 = temp;
            temp = temp->next;
            delete_a_message(&player->messages, temp2);
        } else {
            temp = temp->next;
        }
    }
}

void render_messages(player_t *player)
{
    int  i = 0;

    for (messages_t *temp = player->messages; temp; temp = temp->next) {
        draw_text(player, temp->text, (sfVector4i_t){player->param.size.x / 2 -
            (strlen(temp->text) / 2 * 4 * 3), 30 + i * 10 * 3, 3, UX_CHN},
            sfWhite);
        i++;
    }
}
