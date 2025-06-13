/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Parse main file for configuration
*/
#include "wolf.h"

static int is_valid(const char *str)
{
    return (!my_lstrcmp(str, "id") || !my_lstrcmp(str, "name"));
}

static int ntext_id(wolf_context_t *context, char *id)
{
    int i = 0;

    if (!my_str_isnum(id)) {
        return 0;
    }
    for (textures_t *temp = context->textures; temp; temp = temp->next) {
        if (atoi(id) == temp->id) {
            i++;
        }
    }
    return i;
}

static int ntext_name(wolf_context_t *context, char *id)
{
    int i = 0;

    for (textures_t *temp = context->textures; temp; temp = temp->next) {
        if (!strcmp(id, temp->name)) {
            i++;
        }
    }
    return i;
}

static void handle_unique(char **warray, int *i, int *is_unique)
{
    if (!my_lstrcmp(warray[*i], "unique")) {
        *is_unique = 1;
        (*i)++;
    }
}

int check_if_texture_exists(char **warray, wolf_context_t *context, int *err)
{
    int is_unique = 0;
    int (*check)(wolf_context_t *, char *);
    int a = 0;
    int i = 0;

    for (; warray[i]; i++) {
        is_unique = 0;
        if (!is_valid(warray[i]))
            return i;
        check = (!my_lstrcmp(warray[i], "id")) ? &ntext_id : &ntext_name;
        i++;
        handle_unique(warray, &i, &is_unique);
        a = check(context, warray[i]);
        if (!a || (is_unique && a > 1)) {
            *err = 1;
            fprintf(stderr, PROGNAME": No texture \"%s\" found.\n", warray[i]);
            return i;
        }
    }
    return i;
}
