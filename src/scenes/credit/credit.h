/*
** EPITECH PROJECT, 2024
** credit
** File description:
** credit header
*/

#ifndef CREDIT_H
    #define CREDIT_H

    #include "wolf.h"

typedef struct credit_s {
    sfTexture *texture_bg_credit;
    sfSprite *background_credit;
    sfText *text_credit;
    sfFont *font;
    unsigned int font_size;
} credit_t;

// Initialization functions
void init_credit_background(bst_context_t *window);
void init_credit_text(bst_context_t *window);

#endif // CREDIT_H
