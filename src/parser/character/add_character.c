/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add Character with parsing
*/
#include "wolf.h"
#include <string.h>
#include "sound.h"
#include "parser.h"

const skill_tab_t skill_tab[8] = {
    {"heal", &skill_heal, &skill_heal_end, 45000.f, 35000.f},
    {"wall", &skill_wall, &skill_wall_end, 60000.f, 30000.f},
    {"atk", &skill_atk, &skill_atk_end, 30000.f, 10000.f},
    {"dash", &skill_dash, &skill_dash_end, 5000.f, 0.f},
    {"bleed", &skill_bleeding, &skill_bleeding_end, 30000.f, 20000.f},
    {"invisible", &skill_invisible, &skill_invisible_end, 45000.f, 30000.f},
    {"steal", &skill_steal, &skill_steal_end, 1000.f, 0.f},
    {"tp", &skill_tp, &skill_tp_end, 60000.f, 0.f},
};

static int sounds_exists(char **warray, wolf_context_t *context)
{
    for (int i = 0; warray[i] && i < 7; i++) {
        if (!get_sound(context->w_sound.sounds, warray[i])) {
            printf("%s does not exists\n", warray[i]);
            return ERROR;
        }
    }
    return OK;
}

static voicelines_t create_voicelines(char **warray, wolf_context_t *context)
{
    voicelines_t sounds;
    sounds_t *s = context->w_sound.sounds;

    sounds.reload = sfSound_create();
    sfSound_setBuffer(sounds.reload, get_sound(s, warray[6])->soundbuffer);
    sounds.midlife = sfSound_create();
    sfSound_setBuffer(sounds.midlife, get_sound(s, warray[7])->soundbuffer);
    sounds.death = sfSound_create();
    sfSound_setBuffer(sounds.death, get_sound(s, warray[8])->soundbuffer);
    sounds.skill = sfSound_create();
    sfSound_setBuffer(sounds.skill, get_sound(s, warray[9])->soundbuffer);
    sounds.shot = sfSound_create();
    sfSound_setBuffer(sounds.shot, get_sound(s, warray[10])->soundbuffer);
    sounds.heal = sfSound_create();
    sfSound_setBuffer(sounds.heal, get_sound(s, warray[11])->soundbuffer);
    sounds.selection = sfSound_create();
    sfSound_setBuffer(sounds.selection, get_sound(s, warray[12])->soundbuffer);
    sounds.win = sfSound_create();
    sfSound_setBuffer(sounds.win, get_sound(s, warray[13])->soundbuffer);
    return sounds;
}

static int create_skill(character_t *c, char *skill, wolf_context_t *context)
{
    (void)context;
    for (int i = 0; i < 8; i++) {
        if (!strcmp(skill_tab[i].command, skill)) {
            c->skill = skill_tab[i].skill;
            c->endskill = skill_tab[i].endskill;
            c->skill_cooldown = skill_tab[i].skill_cooldown;
            c->endskill_cooldown = skill_tab[i].endskill_cooldown;
            return OK;
        }
    }
    printf(PROGNAME": No skill named %s\n", skill);
    return ERROR;
}

int add_character_p(char **warray, wolf_context_t *context)
{
    character_t *character = malloc(sizeof(character_t));

    if (my_len_word_array(warray) < 18 || !character) {
        return ERROR;
    }
    context->n_chars++;
    context->characters = realloc(context->characters,
        sizeof(character_t *) * context->n_chars);
    context->characters[context->n_chars - 1] = character;
    character->name = strdup(warray[1]);
    character->apparance = get_texture(context->textures, warray[2]);
    character->projectile = get_texture(context->textures, warray[3]);
    character->self = get_texture(context->textures, warray[4]);
    if (sounds_exists(&warray[6], context) == ERROR) {
        return ERROR;
    }
    create_skill(character, warray[5], context);
    character->voicelines = create_voicelines(warray, context);
    character->atk = atof(warray[14]);
    character->maxhp = atof(warray[15]);
    character->cooldown_till_shot = atof(warray[16]);
    character->ammo = atoi(warray[17]);
    return OK;
}
