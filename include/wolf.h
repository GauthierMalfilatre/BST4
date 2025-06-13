/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for the wolf3d project.
*/
#ifndef WOLF_3D_H
    #define WOLF_3D_H

    #define ERROR 84
    #define OK 0
    #define NSCENE 7
    #define PROGNAME "Feeria BST"

    #define CONFIG_FILE "./save/maps/arena.ray"

    #define MIN_FPS 30
    #define MAX_FPS 240

    #define MIN_SENSI 1
    #define MAX_SENSI 100

    #define FIRE_TIME 4000.f
    #define DEFIRE_TIME 4000.f

    #define MIN_SOUND 0
    #define MAX_SOUND 100
    #define PI 3.1415926535897932384626433832795028841f
    #define DEG_TO_RAD(angle) (((angle) / 180.0) * PI)
    #define ABS(n) ((n) > 0 ? (n) : -1 * (n))
    #define SQUARE(n) ((n) * (n))
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define PLAYER_Z 50
    #define PLAYER_HFOV 90
    #define FLOOR_Z 5
    #define FLOOR_TILE_SIZE 50.0
    #define PLAYER_HEIGHT (PLAYER_Z - FLOOR_Z)
    #define SAFE_MARGIN 3.0f

    #define TMP_CHN -1.f
    #define SELF_CHN -2.f
    #define UX_CHN -3.f

    #define SETTING_PATH "./save/setting.ini"
    #define NWIN 6

    #include "my.h"
    #include "../src/context/context.h"
    #include "../src/rain/rain.h"
    #include "../src/utils/utils.h"
    #include "../src/maps/maps.h"
    #include "../src/render/raycaster/framebuffer/font/wolf_font.h"
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <math.h>
    #include <stdio.h>
    #include <dirent.h>
    #include <string.h>

void made_team_win(wolf_context_t *context, int team);
void give_point_to_team(wolf_context_t *context, const int np);
void rumble_controller(player_t *player);

#endif /* WOLF_3D_H */
