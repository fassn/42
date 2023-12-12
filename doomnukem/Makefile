# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:42 by vtouffet          #+#    #+#              #
#    Updated: 2019/09/11 20:50:41 by cfargere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SDL_VERSION=SDL2-2.0.10
OS := $(shell uname -s)
ifeq ($(OS),Linux)
	SDL=sdl2_linux
endif
ifeq ($(OS),Darwin)
	SDL=sdl2_mac
endif

SRCS_GAME_PATH=./srcs/game/
SRCS_GAME_FILES=main.c					\
                struct.c				\
				render.c				\
                draw_wall.c				\
				draw_floor_ceiling.c	\
				draw_gui.c				\
				draw_sprite.c			\
				draw_sprite2.c			\
				init_sprite.c			\
                parser.c				\
                data.c					\
				get_texture.c			\
                load_texture.c			\
                hook_mouse.c			\
				hook_keyboard.c			\
                raycast.c				\
				utils.c					\
				move.c					\
				color.c					\
				enemy.c					\
				object.c				\
				hud.c					\
				gui.c					\
				door.c					\
				decal.c					\
				loader_utils.c			\
				loader_xpm.c
				# bmp_parser.c
SRCS_GAME=$(addprefix $(SRCS_GAME_PATH), $(SRCS_GAME_FILES))

SRCS_EDITOR_PATH=./srcs/editor/
SRCS_EDITOR_FILES=cli.c display.c events.c file.c init.c texture.c resize.c utils.c \
				  display_ui.c free.c ../game/loader_xpm.c ../game/loader_utils.c
SRCS_EDITOR=$(addprefix $(SRCS_EDITOR_PATH), $(SRCS_EDITOR_FILES))

OBJECTS_GAME_PATH=./objs/game/
OBJECTS_GAME_FILES=$(SRCS_GAME_FILES:.c=.o)
OBJECTS_GAME=$(addprefix $(OBJECTS_GAME_PATH), $(OBJECTS_GAME_FILES))

OBJECTS_EDITOR_PATH=./objs/editor/
OBJECTS_EDITOR_FILES=$(SRCS_EDITOR_FILES:.c=.o)
OBJECTS_EDITOR=$(addprefix $(OBJECTS_EDITOR_PATH), $(OBJECTS_EDITOR_FILES))

ifeq ($(OS),Linux)
	CC=clang
	COMPILE=-Wall -Wextra -Werror -g3
endif
ifeq ($(OS),Darwin)
	CC=gcc
	COMPILE=-Wall -Wextra -Werror -g3
endif

INCLUDES=-I./libs/libft
HEADER_GAME=./inc/doomnukem.h
HEADER_EDITOR=./inc/editor/doomnukem.h ./inc/editor/prototypes.h ./inc/editor/structs.h ./inc/game/xpm_parser_struct.h

LIBFT_NAME=libft.a
LIBFT_PATH=./libs/libft/
LIBFT=$(LIBFT_PATH)$(LIBFT_NAME)

LIBSDL=-lSDL2 -lSDL2_ttf -lSDL2_mixer

COLOR_RESET=\033[0m
COLOR_PENDING=\033[0;33m
COLOR_SUCCESS=\033[0;32m
COLOR_DEFAULT=\033[1;34m

all: $(SDL) libft doom-nukem
	@echo "        [$(COLOR_SUCCESS)DONE$(COLOR_RESET)]"

libft:
	@echo "$(LIBFT_NAME)     [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@make -C $(LIBFT_PATH) > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "$(LIBFT_NAME) [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

sdl2_linux:
	@echo "Enter root password to install SDL2"
	@sudo apt-get install libsdl2-2.0-0 libsdl2-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev

sdl2_mac:
	@brew install sdl2 sdl2_ttf sdl2_mixer
	# @cp -r ~/.brew/include/SDL2 .
	# @cp -f ~/.brew/Cellar/sdl2/2.0.9_1/lib/libSDL2-2.0.0.dylib SDL2/.

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

doom-nukem: $(OBJECTS_GAME) $(LIBFT)
	@echo $(COMPILE)
	@echo "game	[$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@$(CC) $(COMPILE) $(OBJECTS_GAME) $(LIBFT) $(LIBSDL) -lm -pthread -o doom-nukem > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "game	[$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

$(OBJECTS_GAME_PATH)%.o: $(SRCS_GAME_PATH)%.c $(HEADER_GAME)
	@mkdir -p $(OBJECTS_GAME_PATH) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(COMPILE) $(INCLUDES) -c $< -o $@
	@echo "Compiled $@" > /dev/null

editor: $(OBJECTS_EDITOR) $(LIBFT)
	@echo "editor     [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@$(CC) $(COMPILE) $(OBJECTS_EDITOR) $(LIBFT) $(LIBSDL) -lm -o editor > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "editor  [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

$(OBJECTS_EDITOR_PATH)%.o: $(SRCS_EDITOR_PATH)%.c $(HEADER_EDITOR)
	@mkdir -p $(OBJECTS_EDITOR_PATH) 2>/dev/null || echo "" > /dev/null
	@$(CC) $(COMPILE) $(INCLUDES) -I./inc/editor -c $< -o $@
	@echo "Compiled $@" > /dev/null

clean:
	@make -C $(LIBFT_PATH) clean
	@/bin/rm -Rf ./objs

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@/bin/rm -Rf doom-nukem
	@/bin/rm -Rf editor

re: fclean all