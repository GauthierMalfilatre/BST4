/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Move gestion for bst scene.
*/
#include "wolf.h"
#include "scenes.h"

static void do_the_terrible_tragedie_and_made_bouseville_team_not_win(
    wolf_context_t *context)
{
    add_n_rain_drops(&context->bst->rain, 10000);
    eteint_le_noir_mouton(context);
    printf("The 4th edition is finished due to heavy rain !\n");
}

static void pick_sheep(player_t *player, blacksheep_t *bs)
{
    if (bs->is_carried || bs->is_fired || player->equipe != 0) {
        return;
    }
    if (get_norme(*player->x, *player->y, bs->pos.x, bs->pos.y) <= 50.f) {
        printf("Player %s (%p) has pick the blacksheep\n",
            player->name, player);
        bs->is_carried = player;
    }
}

static int get_npfteam(wolf_context_t *context, const int team)
{
    int count = 0;

    for (int i = 0; i < context->n_players; i++) {
        if (context->players[i]->equipe == team &&
            context->players[i]->infos.life > 0.f) {
            count++;
        }
    }
    return count;
}

static void check_endgame(wolf_context_t *context)
{
    if (!context->bst) {
        return;
    }
    if (sfTime_asSeconds(sfClock_getElapsedTime(context->bst->clock)) >
        context->bst->timelimit) {
        if (context->bs->is_fired) {
            give_point_to_team(context, 1000);
            made_team_win(context, 0);
        } else {
            made_team_win(context, 1);
        }
    }
    if (get_npfteam(context, 0) <= 0 && !context->bs->is_fired) {
        made_team_win(context, 1);
    } else if (get_npfteam(context, 1) <= 0) {
        made_team_win(context, 0);
    }
}

static void endskill(wolf_context_t *context, player_t *player)
{
    if (!player->character || !player->character->endskill) {
        return;
    }
    player->character->endskill(context, player, sfFalse);
}

void update_player(wolf_context_t *context, player_t *player)
{
    player->time(player, context);
    if (player->device != -1 && player->infos.life > 0.f) {
        player_resolve_bleeding(player, context);
        player->move(context, player);
        endskill(context, player);
        pick_sheep(player, context->bs);
    }
}

void bst_update(wolf_context_t *context)
{
    if (!context || !context->bst ||
        context->current_scene != GAME_BST_SCENE)
        return;
    if (context->bst->timelimit - sfTime_asSeconds(sfClock_getElapsedTime(
        context->bst->clock)) <= 7.f && context->bs->is_fired &&
        !context->bst->rain && context->wins.x >= 5) {
        do_the_terrible_tragedie_and_made_bouseville_team_not_win(context);
    }
    if (context->bst->is_temp_wall &&
        sfTime_asSeconds(sfClock_getElapsedTime(context->bst->clock)) > 10.f) {
        context->bst->is_temp_wall = sfFalse;
        for (temp_wall_t *temp = context->cmap->temp_walls; temp; temp = temp->next) {
            remove_wall_at_index(&context->cmap->walls, &context->cmap->n_wall, temp->index);
            resolve_others_temp_wall_index(context->cmap->temp_walls, temp->index);
        }
    }
    udpdate_bullets(context);
    update_blacksheep(context);
    for (int i = 0; i < context->n_players; i++) {
        update_player(context, context->players[i]);
    }
    check_endgame(context);
}
