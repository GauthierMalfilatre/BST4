/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Movement of player with keypad
*/
#include "wolf.h"

static void reset_bs(player_t *dst, wolf_context_t *ctx)
{
    if (ctx->bs->is_carried == dst) {
        drop_blacksheep(ctx);
    }
    if (ctx->bs->diffusing == dst) {
        ctx->bs->diffusing = 0;
        ctx->bs->firing = 4000.f;
    }
}

static player_t *get_good_next(wolf_context_t *ctx, player_t *player,
    player_t *killer)
{
    for (int i = 0; i < ctx->n_players; i++) {
        if (ctx->players[i]->equipe == player->equipe &&
            ctx->players[i]->infos.life > 0.f) {
            return ctx->players[i];
        }
    }
    return killer;
}

static void resolve_old_branches(wolf_context_t *ctx, player_t *dst)
{
    for (int i = 0; i < ctx->n_players; i++) {
        if (ctx->players[i] == dst) {
            continue;
        }
        if (ctx->players[i]->infos.life <= 0.f &&
            ctx->players[i]->killer == dst) {
            ctx->players[i]->killer = dst->killer;
        }
    }
}

static void stop_all_voicelines_except_death(player_t *dst)
{
    sfSound_stop(dst->voicelines.heal);
    sfSound_stop(dst->voicelines.midlife);
    sfSound_stop(dst->voicelines.reload);
    sfSound_stop(dst->voicelines.selection);
    sfSound_stop(dst->voicelines.shot);
    sfSound_stop(dst->voicelines.skill);
    sfSound_stop(dst->voicelines.win);
    return;
}

static void resolve_message(player_t *src, player_t *dst)
{
    char buffer[128];

    sprintf(buffer, "You have slain %s", dst->name);
    add_message(&src->messages, 8000.f, buffer, KILL);
    switch (count_messages_with_type(src->messages, KILL)) {
    case 2:
        add_message(&src->messages, 8000.f, "DOUBLE KILL", INFO);
        break;
    case 3:
        add_message(&src->messages, 8000.f, "TRIPLE KILL", INFO);
        break;
    case 4:
        add_message(&src->messages, 8000.f, "QUADRUPLE KILL", INFO);
        break;
    default:
        break;
    }
}

void kill(wolf_context_t *ctx, player_t *dst, player_t *src)
{
    stop_all_voicelines_except_death(dst);
    dst->character->endskill(ctx, dst, sfTrue);
    sfSound_play(dst->voicelines.death);
    src->score += 1000;
    dst->kd.y++;
    printf("Player %s (%p) has kill player %s (%p)\n", src->name, src,
        dst->name, dst);
    dst->killer = get_good_next(ctx, dst, src);
    resolve_old_branches(ctx, dst);
    src->kd.x++;
    reset_bs(dst, ctx);
    resolve_message(src, dst);
    dst->cooldowns.till_respawn = ((ctx->mode == BS_GO) ? -1.f : 10000.f);
}

void deal_damage_to_player(wolf_context_t *ctx, player_t *dst, player_t *src)
{
    if (src->equipe == dst->equipe)
        return;
    if (dst->infos.life > 50 && dst->infos.life - src->infos.atk < 50)
        sfSound_play(dst->voicelines.midlife);
    dst->infos.life -= src->infos.atk;
    dst->is_visible = sfTrue;
    if (dst->bleeding.dps)
        dst->bleeding.target_life -= src->infos.atk;
    if (dst->healing.hps)
        dst->healing.target_life -= src->infos.atk;
    if (src->is_bleeding_others) {
        add_bleeding_to_player(dst, 2.5f, 10000.f);
        dst->killer = src;
        add_n_blood_drops(&dst->blood, 100, (sfVector2f){*dst->x, *dst->y});
    }
    if (dst->infos.life <= 0) {
        kill(ctx, dst, src);
    }
}
