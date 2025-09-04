# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:14:14 by psmolin           #+#    #+#              #
#    Updated: 2025/09/03 14:00:00 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
HEADERS = philosophers_bonus.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I.
MK = make -C

#
SRCS = \
	main_bonus.c \
	utils_init_bonus.c \
	utils_lib_bonus.c \
	utils_philo_bonus.c \
	utils_utils_bonus.c
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