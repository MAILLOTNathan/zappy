##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

NAME = lib_string_array.a

CC = gcc

CFLAGS = -Wall -Werror -W -Wextra -I./include -g3 -ggdb

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

TEST_SRC = 	$(wildcard tests/*.c) \
			$(SRC)

all: $(OBJ)
	ar rc $(NAME) $(OBJ)

tests_run:
	$(CC) -o unit_tests $(TEST_SRC) $(CFLAGS) $(LDFLAGS) --coverage -lcriterion
	./unit_tests
	gcovr --exclude tests/
	gcovr -b --exclude tests/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

tests_clean:
	$(RM) unit_tests
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) *.gcov

re: fclean all
