NAME = ft_shmup

CC = c++ -Ofast -g
CC += -Wall -Wextra -Werror

SRCS = src/main.cpp \

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(SRCS) -Iincludes/ -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t PROJECT COMPILED$(RESET)"

clean:
	@echo "$(RED)[$(NAME)]:\t CLEAN$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

arg =

test: all
	./$(NAME)

val: all
	valgrind ./$(NAME)

#COLORS

GREEN=\e[0;32m
RED=\e[0;91m
BLUE=\e[0;34m
RESET=\e[0m