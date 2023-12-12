# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfargere <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/19 22:30:14 by cfargere          #+#    #+#              #
#    Updated: 2019/01/07 17:53:33 by cfargere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC =	ft_check.c \
		ft_grid_functions.c \
		ft_solver.c \
		ft_tetriminos.c \
		ft_tetriminos2.c \

OBJ = $(SRC:%.c=%.o)

HEADERS = fillit.h $(LIBFT)/libft.h

LIBFT = ./libft

LIB = ./libft/libft.a

all: fillit

fillit: $(OBJ)
	make -C $(LIBFT) re
	$(CC) $(FLAGS) -c $(SRC)
	$(CC) $(FLAGS) $(OBJ) -o $@ $(LIB)

clean:
	make -C $(LIBFT) clean
	/bin/rm $(LIBFT)/$(OBJ)

fclean: 
	make -C $(LIBFT) fclean
	/bin/rm $(OBJ)
	/bin/rm -f fillit

re: fclean all
