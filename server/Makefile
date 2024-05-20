##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

CC = gcc

NAME = zappy_server

SRC = 	main.c \
		$(wildcard src/*.c) \

CFLAGS = -W -Werror -Wall -Wextra -I./include

OBJ = $(SRC:.c=.o)

TEST_SRC = 	$(wildcard tests/*.c) \
			$(wildcard src/*.c)

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

debug:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g3 -ggdb

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	$(CC) -o unit_tests $(TEST_SRC) $(CFLAGS) --coverage -lcriterion
	./unit_tests
	gcovr --exclude tests/
	gcovr -b --exclude tests/

tests_clean:
	$(RM) unit_tests
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) *.gcov
