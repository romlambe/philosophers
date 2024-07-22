# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romlambe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 14:16:39 by romlambe          #+#    #+#              #
#    Updated: 2024/07/19 10:29:36 by romlambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
AUTHOR = romlambe

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC := main.c action.c init.c monitor.c threads.c utils.c

OBJ = $(SRC:.c=.o)

GREEN = \033[0;32m
NC = \033[0m

all: intro $(NAME)

intro:
	@echo "\n==================================="
	@echo "Compiling:	$(NAME)"
	@echo "Author:		$(AUTHOR)"
	@echo "==================================="

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\n$(GREEN)Philo is created.$(NC)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(GREEN)Philo: Cleaning object files..."
	@rm -rf $(OBJ)

fclean: clean
	@echo "$(GREEN)Philo: Cleaning all build files..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
