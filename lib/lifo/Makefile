##
## EPITECH PROJECT, 2025
## LIBLIFO
## File description:
## Static library for a stack / lifo linked list lib
##
SRC = 	create_lifo.c \
		push_lifo.c \
		pull_lifo.c \
		del_lifo.c \

OBJ = $(SRC:.c=.o)

NAME = liblifo.a
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../$(NAME)

.PHONY: clean
clean:
	find -name "*.o" -delete

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
