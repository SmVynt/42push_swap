# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:14:14 by psmolin           #+#    #+#              #
#    Updated: 2025/06/10 14:25:04 by psmolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = push_swap
NAME_CHECKER = checker
SRCS_DIR = src/
HEADERS = $(SRCS_DIR)push_swap.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I. -g
MK = make -C

#
SRCS = \
	$(SRCS_DIR)initialize.c \
	$(SRCS_DIR)solver.c \
	$(SRCS_DIR)swap_commands.c \
	$(SRCS_DIR)swap_commands_r.c \
	$(SRCS_DIR)swap_commands_rr.c \
	$(SRCS_DIR)swap_commands_sp.c \
	$(SRCS_DIR)utils_lib.c \
	$(SRCS_DIR)utils_lists.c \
	$(SRCS_DIR)utils_lists2.c \
	$(SRCS_DIR)utils_solver.c \
	$(SRCS_DIR)utils_error.c
OBJS = $(SRCS:.c=.o)
SRC_PUSHSWAP = $(SRCS_DIR)main_pushswap.c
OBJ_PUSHSWAP =$(SRC_PUSHSWAP:.c=.o)
SRC_CHECKER = $(SRCS_DIR)main_checker_bonus.c
OBJ_CHECKER =$(SRC_CHECKER:.c=.o)

GNL_FOLDER = src/gnl/
GNL_LIB = $(GNL_FOLDER)libgnl.a
GNL_FLAGS = -L$(GNL_FOLDER) -lgnl

#
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: makeall $(NAME) $(NAME_CHECKER)

makeall:
	$(MK) $(GNL_FOLDER) all

$(NAME): $(OBJS) $(OBJ_PUSHSWAP)
	$(CC) $(CFLAGS) $(OBJS) $(OBJ_PUSHSWAP) $(GNL_FLAGS) $(GNL_LIB) -o $(NAME)

$(NAME_CHECKER): $(OBJS) $(OBJ_CHECKER)
	$(CC) $(CFLAGS) $(OBJS) $(OBJ_CHECKER) $(GNL_FLAGS) $(GNL_LIB) -o $(NAME_CHECKER)

clean:
	$(MK) $(GNL_FOLDER) clean
	$(RM) $(OBJS)
	$(RM) $(OBJ_PUSHSWAP)
	$(RM) $(OBJ_CHECKER)

fclean:
	$(MK) $(GNL_FOLDER) fclean
	$(RM) $(OBJS)
	$(RM) $(OBJ_PUSHSWAP)
	$(RM) $(OBJ_CHECKER)
	$(RM) $(NAME)
	$(RM) $(NAME_CHECKER)

re: fclean all

bonus: all

norm:
	norminette \
		$(SRCS_DIR)main_pushswap.c \
		$(SRCS_DIR)main_checker_bonus.c \
		$(SRCS_DIR)initialize.c \
		$(SRCS_DIR)solver.c \
		$(SRCS_DIR)swap_commands.c \
		$(SRCS_DIR)swap_commands_r.c \
		$(SRCS_DIR)swap_commands_rr.c \
		$(SRCS_DIR)swap_commands_sp.c \
		$(SRCS_DIR)utils_lib.c \
		$(SRCS_DIR)utils_lists.c \
		$(SRCS_DIR)utils_lists2.c \
		$(SRCS_DIR)utils_error.c \
		$(SRCS_DIR)utils_solver.c \
		$(SRCS_DIR)push_swap.h

.PHONY: all clean fclean re bonus norm
