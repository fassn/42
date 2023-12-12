# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 13:55:35 by cfargere          #+#    #+#              #
#    Updated: 2019/08/24 02:38:59 by cfargere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname -s)

NAME = wolf3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror
SRC =	src/main.c \
		src/parser.c \
		src/event_handler.c \
		src/player.c \
		src/raycast.c \
		src/vectors.c \
		src/draw.c \
		src/texture_parser.c \

LIBFT_DIR = ./libft/
SDL2_DIR = ./SDL2/
ifeq ($(OS),Linux)
	INCLUDE = -I include
	LIB = -L $(LIBFT_DIR) -lft -lSDL2 -lm
endif
ifeq ($(OS),Darwin)
	INCLUDE = -I include -I SDL2
	LIB = -L $(LIBFT_DIR) -lft -L $(SDL2_DIR) -l SDL2-2.0.0 -lm
endif
OBJ = $(SRC:.c=.o)

SDL_VERSION=SDL2-2.0.10
ifeq ($(OS),Linux)
	SDL=sdl2_linux
endif
ifeq ($(OS),Darwin)
	SDL=sdl2_mac
endif

all: $(SDL) $(NAME)

$(NAME): $(INC_PATH) $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) -o $(NAME) $(OBJ) $(INCLUDE) $(LIB)

%.o: %.c ./include/wolf3d.h
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

sdl2_linux:
	@echo "Enter root password to install SDL2"
	@sudo apt-get install libsdl2-2.0-0 libsdl2-dev

sdl2_mac:
	@brew install sdl2
	@cp -r ~/.brew/include/SDL2 .
	@cp -f ~/.brew/Cellar/sdl2/2.0.9_1/lib/libSDL2-2.0.0.dylib SDL2/.

sdl2_source:
	@curl -a https://www.libsdl.org/release/$(SDL_VERSION).tar.gz --output $(SDL_VERSION).tar.gz
	@tar -xvzf $(SDL_VERSION).tar.gz
	@/bin/rm $(SDL_VERSION).tar.gz
	@mv $(SDL_VERSION) libs
	@(cd libs/$(SDL_VERSION) && ./configure)
	@(cd libs/$(SDL_VERSION) && make)
	@echo "Enter root password to install SDL2 in path"
	@(sudo -A zsh -c "cd libs/$(SDL_VERSION) && make install")
	@/bin/rm -Rf libs/$(SDL_VERSION)

clean:
	@make -C $(LIBFT_DIR) clean
	@/bin/rm -Rf $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@/bin/rm -Rf $(NAME)

re: fclean all
