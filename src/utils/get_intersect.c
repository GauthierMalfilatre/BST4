/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for the wolf3d project.
*/
#include "wolf.h"
#include "utils.h"

static int compute_intersection_point(sfVector2f lines[2],
    wall_t *wall, long double *px, long double *py)
{
    sfVector2f line0 = lines[0];
    sfVector2f line1 = lines[1];
    long double a = line1.x - line0.x;
    long double b = wall->b.x - wall->a.x;
    long double c = wall->a.x - line0.x;
    long double d = line1.y - line0.y;
    long double e = wall->b.y - wall->a.y;
    long double f = wall->a.y - line0.y;
    long double delta = a * e - d * b;
    long double s = c * e - f * b;
    long double t = c * d - f * a;

    if (!delta || (delta > 0 && (s < 0 || s > delta || t < 0 || t > delta)) ||
        (delta < 0 && (s > 0 || s < delta || t > 0 || t < delta)))
        return ERROR;
    *px = line0.x + (s / delta) * a;
    *py = line0.y + (s / delta) * d;
    return OK;
}

int get_intersect(wall_t *wall, sfVector2f line0, sfVector2f line1,
    sfVector2f *intersect)
{
    long double px;
    long double py;

    if (compute_intersection_point((sfVector2f[2]){line0, line1},
        wall, &px, &py) == ERROR)
        return ERROR;
    if (isnan(intersect->x) || isnan(intersect->y) ||
        get_norme(line0.x, line0.y, px, py) <
        get_norme(line0.x, line0.y, intersect->x, intersect->y)) {
        intersect->x = px;
        intersect->y = py;
        return OK;
    }
    return ERROR;
}
