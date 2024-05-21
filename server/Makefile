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
CFLAGS += -I./libs/string_array/include -I./libs/list/include

LDFLAGS = -L./libs/string_array -l_string_array -L./libs/list -llist

OBJ = $(SRC:.c=.o)

TEST_SRC = 	$(wildcard tests/*.c) \
			$(wildcard src/*.c)

all: lib_string_array lib_list $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

debug: lib_string_array lib_list
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LDFLAGS) -g3 -ggdb

lib_list:
	make -C libs/list

lib_list_clean:
	make clean -C libs/list

lib_list_fclean:
	make fclean -C libs/list

lib_list_re:
	make re -C libs/list

lib_string_array:
	make -C libs/string_array

lib_string_array_clean:
	make clean -C libs/string_array

lib_string_array_fclean:
	make fclean -C libs/string_array

lib_string_array_re:
	make re -C libs/string_array

clean: lib_string_array_clean lib_list_clean
	rm -f $(OBJ)

fclean: lib_string_array_fclean lib_list_fclean clean
	rm -f $(NAME)

re: lib_string_array_re lib_list_re fclean all

tests_run:
	$(CC) -o unit_tests $(TEST_SRC) $(CFLAGS) $(LDFLAGS) --coverage -lcriterion
	./unit_tests
	gcovr --exclude tests/
	gcovr -b --exclude tests/

tests_clean:
	$(RM) unit_tests
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) *.gcov
