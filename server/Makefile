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
		$(wildcard src/amber_world/*.c) \
		$(wildcard src/amber_command_server/*.c) \
		$(wildcard src/amber_command_ai/*.c) \
		$(wildcard src/amber_command_logic/*.c) \
		$(wildcard src/amber_command_graphical/*.c) \

CFLAGS = -W -Werror -Wall -Wextra -I./include
CFLAGS += -I./libs/string_array/include -I./libs/list/include
CFLAGS += -I./libs/map

LDFLAGS = -L./libs/string_array -l_string_array -L./libs/list -llist
LDFLAGS += -L./libs/map -lmap

OBJ = $(SRC:.c=.o)

TEST_SRC = 	$(wildcard tests/*.c) \
			$(wildcard src/*.c) \
			$(wildcard src/amber_world/*.c) \
			$(wildcard src/amber_command_server/*.c) \
			$(wildcard src/amber_command_ai/*.c) \
			$(wildcard src/amber_command_logic/*.c) \
			$(wildcard src/amber_command_graphic/*.c) \

TEST_GREP = $(wildcard tests/GREP*.c) \
			$(wildcard src/*.c) \
			$(wildcard src/amber_world/*.c) \
			$(wildcard src/amber_command_server/*.c) \
			$(wildcard src/amber_command_ai/*.c) \
			$(wildcard src/amber_command_logic/*.c) \
			$(wildcard src/amber_command_graphic/*.c) \

all: lib_string_array lib_list lib_map $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

debug: lib_string_array lib_list lib_map
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

lib_map:
	make -C libs/map

lib_map_clean:
	make clean -C libs/map

lib_map_fclean:
	make fclean -C libs/map

lib_map_re:
	make re -C libs/map

clean: lib_string_array_clean lib_list_clean lib_map_clean
	rm -f $(OBJ)

fclean: lib_string_array_fclean lib_list_fclean lib_map_fclean clean
	rm -f $(NAME)

re: lib_string_array_re lib_list_re fclean lib_map_re all

tests_run: lib_string_array lib_list
	$(CC) -o unit_tests $(TEST_SRC) $(CFLAGS) $(LDFLAGS) --coverage -lcriterion
	./unit_tests
	gcovr --exclude tests/
	gcovr -b --exclude tests/

tests_run_GREP: lib_string_array lib_list
	$(CC) -o unit_tests $(TEST_GREP) $(CFLAGS) $(LDFLAGS) --coverage \
	-lcriterion
	./unit_tests
	gcovr --exclude tests/GREP*.c
	gcovr -b --exclude tests/GREP*.c

tests_clean:
	$(RM) unit_tests
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) *.gcov
