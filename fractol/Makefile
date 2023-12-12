# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfargere <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 13:36:46 by cfargere          #+#    #+#              #
#    Updated: 2019/04/12 16:20:41 by cfargere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT_FOLD = libft/
LIBFT = libft/libft.a

MLX = /usr/local/lib
MLX_INC = /usr/local/include

LIB_LNX = -lmlx -lXext -lX11 -lpthread -lm
LIB_MAC = -lmlx -framework OpenGL -framework Appkit -lpthread -lm

SRC =	main.c \
		mandelbrot.c \
		julia.c \
		burningship.c \
		hooks.c \
		zoom.c \

INC = fractol.h

OBJ = $(SRC:.c=.o)

all: $(NAME) $(LIBFT_FOLD)

$(NAME): $(LIBFT_FOLD) Makefile $(OBJ)
	@make -C $(LIBFT_FOLD)
	$(CC) -I $(MLX_INC) $(OBJ) $(LIBFT) -L $(MLX) $(LIB_LNX) -o $(NAME)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make -C $(LIBFT_FOLD) clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_FOLD) fclean
	@/bin/rm -f $(NAME) 
	@echo "CLEAN ./fractol"
	@echo "CLEAN *.o files"

re: fclean all
