/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Header file for scenes.
*/
#ifndef UTILS_WOLF_3D_H
    #define UTILS_WOLF_3D_H

double get_norme(long double x1, long double y1, long double x2,
    long double y2);
int get_intersect(wall_t *wall, sfVector2f line0, sfVector2f line1,
    sfVector2f *intersect);
char is_mouse_over_button(const sfRectangleShape *button,
    sfVector2f mouse_pos);
void update_text_pos(sfRectangleShape *bouton, sfText *text);
void update_text(sfText *text, const char *str);

int my_lstrcmp(const char *s1, const char *s2);

void draw_string(sfRenderWindow *window, char *str, sfVector2f pos,
    sfVector2f size);

#endif /* UTILS_WOLF_H */
