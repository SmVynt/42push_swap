# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:14:14 by psmolin           #+#    #+#              #
#    Updated: 2025/08/31 18:48:33 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
NAME_B = philosophers_bonus
SRCS_DIR = philo/
SRCS_B_DIR = philo_bonus/
HEADERS = $(SRCS_DIR)philosophers.h
HEADERS_B = $(SRCS_B_DIR)philosophers_bonus.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I. -pthread
MK = make -C

#
SRCS = \
	$(SRCS_DIR)main.c \
	$(SRCS_DIR)utils_error.c \
	$(SRCS_DIR)utils_init.c \
	$(SRCS_DIR)utils_lib.c \
	$(SRCS_DIR)utils_threads.c
OBJS = $(SRCS:.c=.o)
SRC_B = \
	$(SRCS_B_DIR)main_bonus.c \
	$(SRCS_B_DIR)utils_init_bonus.c \
	$(SRCS_B_DIR)utils_lib_bonus.c \
	$(SRCS_B_DIR)utils_philo_bonus.c \
	$(SRCS_B_DIR)utils_utils_bonus.c
OBJS_B =$(SRC_B:.c=.o)

#
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%_bonus.o: %_bonus.c $(HEADERS_B)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_B)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re bonus
