/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Create players.
*/
#include "wolf.h"
#include "math.h"

// Warning ! Decrease bleeding target_lifr when taking damage to
//    annulation of bleeding when taking others damages
static void global_bleeding(player_t *self, wolf_context_t *context)
{
    if (!self->bleeding.dps) {
        return;
    }
    self->infos.life -= self->bleeding.dps * (self->delta_t / 1000.f);
    self->bleeding.time_elapsed += self->delta_t;
    if (self->bleeding.time_elapsed >= self->bleeding.duration ||
        self->infos.life < self->bleeding.target_life) {
        reinit_bleeding(&self->bleeding);
    }
    if (self->infos.life > 0.f) {
        return;
    }
    self->cooldowns.till_respawn = ((context->mode == BS_GO) ? -1.f : 10000.f);
    if (self->killer) {
        self->killer->score += 1000.f;
    }
}

static void global_healing(player_t *self, wolf_context_t *context)
{
    (void) context;
    if (!self->healing.hps) {
        return;
    }
    self->infos.life += self->healing.hps * (self->delta_t / 1000.f);
    self->healing.time_elapsed += self->delta_t;
    if (self->healing.time_elapsed >= self->healing.duration ||
        self->infos.life > self->healing.target_life) {
        reinit_healing(&self->healing);
    }
}

void add_healing_to_player(player_t *player, const float hps,
    const float duration)
{
    printf("Player %s (%p) have receive healing with %.1f dps during %.1f"
        " seconds.\n", player->name, player, hps, duration / 1000.f);
    player->healing.base_life = player->infos.life;
    player->healing.hps = hps;
    player->healing.duration = duration;
    player->healing.time_elapsed = 0.f;
    player->healing.target_life = player->infos.life + hps *
        duration / 1000.f;
    if (player->healing.target_life > player->character->maxhp) {
        player->healing.target_life = player->character->maxhp;
    }
}

void reinit_healing(healing_t *healing)
{
    healing->base_life = 0.f;
    healing->target_life = 0.f;
    healing->duration = 0.f;
    healing->time_elapsed = 0.f;
    healing->hps = 0.f;
}

void add_bleeding_to_player(player_t *player, const float dps,
    const float duration)
{
    printf("Player %s (%p) have receive bleeding with %.1f dps during %.1f"
        " seconds.\n", player->name, player, dps, duration / 1000.f);
    player->bleeding.base_life = player->infos.life;
    player->bleeding.dps = dps;
    player->bleeding.duration = duration;
    player->bleeding.time_elapsed = 0.f;
    player->bleeding.target_life = player->infos.life - dps *
        duration / 1000.f;
    if (player->bleeding.target_life < 0.f) {
        player->bleeding.target_life = 0.f;
    }
    reinit_healing(&player->healing);
}

void reinit_bleeding(bleeding_t *bleeding)
{
    bleeding->base_life = 0.f;
    bleeding->target_life = 0.f;
    bleeding->duration = 0.f;
    bleeding->time_elapsed = 0.f;
    bleeding->dps = 0.f;
}

void player_resolve_bleeding(player_t *player, wolf_context_t *context)
{
    global_healing(player, context);
    global_bleeding(player, context);
}
