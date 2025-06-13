/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Clear the framebuffer.
*/
#include "../../../../include/wolf.h"
#include "../../render.h"

#include <SFML/Graphics.h>
#include <stdint.h>

sfColor blend_rgb332(sfColor dst, sfColor src, float alpha)
{
    unsigned char color[3];

    color[0] = (src.r * alpha * 2 + dst.r * (1 - alpha) * 2) / 2;
    color[1] = (src.g * alpha * 2 + dst.g * (1 - alpha) * 2) / 2;
    color[2] = (src.b * alpha * 2 + dst.b * (1 - alpha) * 2) / 2;
    return (sfColor){color[0], color[1], color[2], 255};
}
