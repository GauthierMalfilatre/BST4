/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../render.h"
#include "thread.h"

static void *thread_render_player(void *arg)
{
    thread_args_t *args = (thread_args_t *)arg;

    if (!args || !args->context || !args->player)
        return NULL;
    player_render(args->context, args->player);
    return NULL;
}

void destroy_render_multithread(wolf_context_t *context)
{
    if (!context || !context->render_manager)
        return;
    if (context->render_manager->threads) {
        free(context->render_manager->threads);
        context->render_manager->threads = NULL;
    }
    if (context->render_manager->args) {
        free(context->render_manager->args);
        context->render_manager->args = NULL;
    }
    free(context->render_manager);
    context->render_manager = NULL;
}

char init_render_multithread(wolf_context_t *context)
{
    context->render_manager = malloc(sizeof(render_manager_t));
    if (!context->render_manager) {
        fprintf(stderr, "Erreur : ender_manager failed\n");
        return ERROR;
    }
    context->render_manager->threads = calloc(context->n_players,
        sizeof(pthread_t));
    context->render_manager->args = calloc(context->n_players,
        sizeof(thread_args_t));
    if (!context->render_manager->threads || !context->render_manager->args) {
        fprintf(stderr, "Erreur : render_manager members failed\n");
        destroy_render_multithread(context);
        return ERROR;
    }
    return OK;
}

void multithread_render(wolf_context_t *context)
{
    if (!context->render_manager) {
        return;
    }
    for (int i = 0; i < context->n_players; i++) {
        context->render_manager->args[i].context = context;
        context->render_manager->args[i].player = context->players[i];
        if (pthread_create(&context->render_manager->threads[i], NULL,
            thread_render_player, &context->render_manager->args[i]) != 0) {
            fprintf(stderr, "failed create thread\n");
        }
    }
    for (int i = 0; i < context->n_players; i++) {
        if (pthread_join(context->render_manager->threads[i], NULL) != 0) {
            fprintf(stderr, "failed join thread\n");
        }
    }
}
