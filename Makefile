# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 21:47:43 by bde-luce          #+#    #+#              #
#    Updated: 2026/03/23 14:40:19 by bde-luce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

INCLUDES = -I$(INC_DIR)

SRCS =	utils.c check_args.c init.c routine_actions.c routine_control.c \
		handle_threads.c philo.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

MSG_BUILD = @echo "🔨 Building $(NAME)..."
MSG_DONE = @echo "✅ Done"
MSG_CLEAN = @echo "🧹 Cleaning object files..."
MSG_FCLEAN = @echo "🧼 Removing executable..."
MSG_RE = @echo "🔁 Rebuilding..."

all: $(NAME)

$(NAME): $(OBJS)
	$(MSG_BUILD)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread
	$(MSG_DONE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "🧱 Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MSG_CLEAN)
	@rm -rf $(OBJ_DIR)
	$(MSG_DONE)

fclean: clean
	$(MSG_FCLEAN)
	@rm -f $(NAME)
	$(MSG_DONE)

re:
	$(MSG_RE)
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
