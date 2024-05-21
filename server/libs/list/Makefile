##
## EPITECH PROJECT, 2024
## mini_http_server
## File description:
## Makefile
##

NAME = liblist.a

CFLAGS = -Wall -Werror -Wextra -W -g3

SRC = 	list.c \
		linked_list.c \

OBJ = $(SRC:.c=.o)

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	find -type f -name "#*#" -delete -o \
	-type f -name "*~" -delete -o -type f -name "*.o" -delete -o \
	-type f -name "*.gc*" -delete

fclean: clean
	rm -f $(NAME)

re: fclean all
