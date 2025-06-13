/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for the wolf3d project.
*/
#ifndef THREAD_H
    #define THREAD_H

    #include "wolf.h"
    #include <pthread.h>

typedef struct {
    wolf_context_t *context;
    player_t *player;
} thread_args_t;

typedef struct render_manager_s {
    pthread_t *threads;
    thread_args_t *args;
} render_manager_t;

#endif /* THREAD_H*/
