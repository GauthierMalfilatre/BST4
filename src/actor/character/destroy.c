/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy players.
*/
#include "wolf.h"

// Character creation is made in parser
static void destroy_character(character_t *character)
{
    sfSound_destroy(character->voicelines.death);
    sfSound_destroy(character->voicelines.heal);
    sfSound_destroy(character->voicelines.midlife);
    sfSound_destroy(character->voicelines.reload);
    sfSound_destroy(character->voicelines.selection);
    sfSound_destroy(character->voicelines.shot);
    sfSound_destroy(character->voicelines.skill);
    sfSound_destroy(character->voicelines.win);
    free(character->name);
    free(character);
    return;
}

int destroy_characters(character_t **characters, const int n_characters)
{
    if (!characters) {
        return ERROR;
    }
    for (int i = 0; i < n_characters && characters[i]; i++) {
        destroy_character(characters[i]);
    }
    free(characters);
    return OK;
}
