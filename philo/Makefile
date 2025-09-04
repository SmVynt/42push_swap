# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:14:14 by psmolin           #+#    #+#              #
#    Updated: 2025/09/04 12:11:39 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADERS = philosophers.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I. -pthread
MK = make -C

#
SRCS = \
	main.c \
	utils_extra.c \
	utils_init.c \
	utils_lib.c \
	utils_philos.c \
	utils_threads.c
OBJS = $(SRCS:.c=.o)

#
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
