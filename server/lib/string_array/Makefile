##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

NAME = lib_string_array.a

CC = gcc

CFLAGS = -Wall -Werror -W -Wextra -I./include

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all