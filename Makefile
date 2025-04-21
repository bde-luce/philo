# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 21:47:43 by bde-luce          #+#    #+#              #
#    Updated: 2025/04/21 18:06:48 by bde-luce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iincludes

SRC_DIR = sources
OBJ_DIR = objs

SRC = utils.c check_args.c init.c routine_actions.c routine_control.c \
      handle_threads.c philo.c

SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ_FILES = $(SRC:%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "$(YELLOW)Linking executable...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -lpthread
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Removing executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
