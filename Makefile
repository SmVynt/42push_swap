# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:14:14 by psmolin           #+#    #+#              #
#    Updated: 2025/06/06 14:03:42 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = push_swap
HEADERS = push_swap.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I.
SRCS_DIR = src/

#
SRCS = \
	$(SRCS_DIR)main.c \
	$(SRCS_DIR)initialize.c \
	$(SRCS_DIR)swap_commands.c \
	$(SRCS_DIR)swap_commands_r.c \
	$(SRCS_DIR)swap_commands_rr.c \
	$(SRCS_DIR)swap_commands_sp.c \
	$(SRCS_DIR)utils_lib.c \
	$(SRCS_DIR)utils_lists.c \
	$(SRCS_DIR)utils_lists2.c \
	$(SRCS_DIR)utils_error.c
OBJS = $(SRCS:.c=.o)
#
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

re: fclean all

bonus: all

norm:
	norminette \
		$(SRCS_DIR)main.c \
		$(SRCS_DIR)initialize.c \
		$(SRCS_DIR)swap_commands.c \
		$(SRCS_DIR)swap_commands_r.c \
		$(SRCS_DIR)swap_commands_rr.c \
		$(SRCS_DIR)swap_commands_sp.c \
		$(SRCS_DIR)utils_lib.c \
		$(SRCS_DIR)utils_lists.c \
		$(SRCS_DIR)utils_lists2.c \
		$(SRCS_DIR)utils_error.c \
		$(SRCS_DIR)push_swap.h

.PHONY: all clean fclean re bonus norm
