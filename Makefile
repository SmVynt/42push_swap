# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:14:14 by psmolin           #+#    #+#              #
#    Updated: 2025/07/09 14:39:47 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philosophers
SRCS_DIR = mandatory/
HEADERS = $(SRCS_DIR)philosophers.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I.
MK = make -C

#
SRCS = \
	$(SRCS_DIR)utils_error.c \
	$(SRCS_DIR)utils_init.c \
	$(SRCS_DIR)utils_lib.c \
	$(SRCS_DIR)utils_threads.c
OBJS = $(SRCS:.c=.o)
SRC_M = $(SRCS_DIR)main.c
OBJ_M =$(SRC_M:.c=.o)

#
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(OBJ_M)
	$(CC) $(CFLAGS) $(OBJS) $(OBJ_M) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_M)

fclean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_M)
	$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
