/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Header file for liblifo
*/
#ifndef LIB_LIFO_H
    #define LIB_LIFO_H
    #include <stdlib.h>

typedef struct lifo_linked_list_s {
    void *stuff;
    struct lifo_linked_list_s *next;
} lifo_linked_list_t;

typedef struct lifo_s {
    lifo_linked_list_t *lifo;
    int size_of_lifo;
} lifo_t;

lifo_t *create_lifo(void);
int push_lifo(lifo_t *lifo, void *stuff);
void *pull_lifo(lifo_t *lifo);
int del_lifo(lifo_t *lifo);

#endif
