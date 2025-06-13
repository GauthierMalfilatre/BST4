/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for the wolf3d project.
*/
#include "wolf.h"
#include "scenes.h"
#include <SDL.h>

void rumble_controller(player_t *player)
{
    return;
    if (player->sdl.h)
        SDL_HapticRumblePlay(player->sdl.h, 1.0f, 500);
}

void change_scene(int new_scene, wolf_context_t *window)
{
    if (new_scene >= 0 && new_scene < NSCENE) {
        scenes[window->current_scene].destroy(window);
        window->current_scene = new_scene;
        scenes[window->current_scene].init(window);
    }
}

void print_framerate(void)
{
    static int first = 1;
    static sfClock * clock;
    static int fps = 0;
    sfTime elapsed;

    if (first == 1) {
        clock = sfClock_create();
        first = 0;
    }
    elapsed = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed) >= 1) {
        printf("%3d FPS\n", fps);
        fflush(stdout);
        fps = 0;
        sfClock_restart(clock);
    } else
        fps++;
}

static int wolf(wolf_context_t *context)
{
    while (sfRenderWindow_isOpen(context->view->window)) {
        while (sfRenderWindow_pollEvent(context->view->window, &context->evt))
            scenes[context->current_scene].event(context);
        scenes[context->current_scene].update(context);
        scenes[context->current_scene].draw(context);
        sfRenderWindow_display(context->view->window);
    }
    return OK;
}

int main(void)
{
    wolf_context_t *context = 0;
    int exitcode = OK;

    if (create_context(&context, CONFIG_FILE) == ERROR) {
        fprintf(stderr, PROGNAME": Exiting due to error when loading game.\n");
        return ERROR;
    }
    if (!context->n_map) {
        destroy_context(context);
        return ERROR;
    }
    context->cmap = context->maps[0];
    if (wolf(context) == ERROR) {
        fprintf(stderr, PROGNAME": Exiting due to error when running game.\n");
        exitcode = ERROR;
    }
    destroy_context(context);
    return exitcode;
}
