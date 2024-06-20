##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

NAME = libmap.a

CFLAGS = -Wall -Werror -W -Wextra -I./include

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
