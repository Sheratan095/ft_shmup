NAME = ft_shmup

CC = c++ -Ofast -g
# CC += -Wall -Wextra -Werror

SRCS = src/main.cpp \
	    src/screen.cpp \
		src/Game.cpp \
		src/menù.cpp \

LIBS = -lncurses

VALGRIND =  valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --suppressions=valgrind.supp

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(SRCS) $(LIBS) -Iincludes/ -o  $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t PROJECT COMPILED$(RESET)"

clean:
	@echo "$(RED)[$(NAME)]:\t CLEAN$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

arg =

test: re
	./$(NAME)
	reset

val: all
	valgrind -suppr ./$(NAME)

#COLORS

GREEN=\e[0;32m
RED=\e[0;91m
BLUE=\e[0;34m
RESET=\e[0m