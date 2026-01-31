##
## EPITECH PROJECT, 2025
## LIBDICT
## File description:
## Static library for a dictionnary
##
SRC = 	src/dict_add_entry.c \
		src/dict_remove_entry.c \
		src/dict_search_entry.c \
		src/dict_clear.c \
		src/dict_dump.c \
		src/dict_change_entry.c \

CFLAGS += -Iinclude/ -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

NAME = libdict.a
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

.PHONY: clean
clean:
	find -name "*.o" -delete

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
