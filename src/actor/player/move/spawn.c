/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Movement of player with keypad
*/
#include "wolf.h"

int spawn(player_t *player, wolf_context_t *context)
{
    spawns_t *spawn = find_spawn_point(context->cmap->spawns,
        player->equipe ? DEF : ATK);

    printf("Player %s (%p) has respawn\n", player->name, player);
    player->infos.life = player->character->maxhp;
    player->infos.atk = player->character->atk;
    player->infos.atkspd = player->character->cooldown_till_shot;
    player->infos.ammo = player->character->ammo;
    player->character->endskill(context, player, sfTrue);
    player->cooldowns = (cooldowns_t){0.f, 0.f, 0.f, 0.f};
    player->base_x = spawn->a.x + rand() % (int)(spawn->b.x - spawn->a.x);
    player->base_y = spawn->a.y + rand() % (int)(spawn->b.y - spawn->a.y);
    player->x = &player->base_x;
    player->y = &player->base_y;
    reinit_bleeding(&player->bleeding);
    sfClock_restart(player->clock);
    player->killer = (player_t *) 0;
    player->angle = &player->base_angle;
    return OK;
}
