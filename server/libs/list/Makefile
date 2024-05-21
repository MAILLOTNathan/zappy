##
## EPITECH PROJECT, 2024
## mini_http_server
## File description:
## Makefile
##

NAME = liblist.a

CFLAGS = -Wall -Werror -Wextra -W -g3 -I./include

SRC = 	list.c \
		linked_list.c \
		utils_list.c

TEST_SRC = 	$(wildcard tests/*.c) \
			$(SRC)

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
