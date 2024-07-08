# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 14:36:26 by pleander          #+#    #+#              #
#    Updated: 2024/07/08 11:35:26 by pleander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := push_swap
CC := cc
#CFLAGS := -Wall -Wextra -Werror
CFLAGS := -Wall -Wextra -Werror -g
CFILES := construct_cmd.c \
		  init_stacks.c \
		  main.c \
		  parse.c \
		  push_swap.c \
		  rev_sort_into_b.c \
		  stack.c \
		  stack2.c \
		  stack_utils.c \
		  utils.c \
		  utils2.c

LIBFT := libft/libft.a

OBJECTS := $(CFILES:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	make clean -C libft

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	make fclean -C libft

.PHONY: re
re: fclean all
