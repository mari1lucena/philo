# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marilins <marilins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/06 16:27:19 by marilins          #+#    #+#              #
#    Updated: 2026/06/07 11:41:15 by marilins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

OBJ_DIR = obj

SRCS = main.c \
	parsing.c \
	initi.c \
	clean.c \
	utils.c \
	simulation.c \
	routine.c \
	monitor.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

HEADER = philosophers.h

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "philo compiled"

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "philo removed"

re: fclean all

.PHONY: all clean fclean re