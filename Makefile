# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:14:14 by psmolin           #+#    #+#              #
#    Updated: 2025/05/11 21:08:35 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = push_swap
HEADERS = push_swap.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I.

#
SRCS = \
		main.c \
		initialize.c \
		swap_commands_1.c \
		utils_lists.c \
		utils.c
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
	norminette	main.c \
		initialize.c \
		swap_commands_1.c \
		utils_lists.c \
		utils.c \
		push_swap.h

.PHONY: all clean fclean re bonus norm
