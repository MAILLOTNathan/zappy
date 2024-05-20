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

CFLAGS = -W -Werror -Wall -Wextra -I./include -I./lib/string_array/include

LDFLAGS = -L./lib/string_array -l_string_array

OBJ = $(SRC:.c=.o)

TEST_SRC = 	$(wildcard tests/*.c) \
			$(wildcard src/*.c)

all: lib_string_array $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

lib_string_array:
	make -C lib/string_array

lib_string_array_clean:
	make clean -C lib/string_array

lib_string_array_fclean:
	make fclean -C lib/string_array

lib_string_array_re:
	make re -C lib/string_array

debug:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LDFLAGS) -g3 -ggdb

clean: lib_string_array_clean
	rm -f $(OBJ)

fclean: lib_string_array_fclean clean
	rm -f $(NAME)

re: lib_string_array_re fclean all

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
