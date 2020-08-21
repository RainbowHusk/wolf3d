# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahusk <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 19:54:33 by ahusk             #+#    #+#              #
#    Updated: 2020/08/13 19:54:35 by ahusk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#OBJS specifies which files to compile as part of the project
OBJS = main.c draw_fov.c draw_map.c draw_rect.c draw_walls.c input_pixel.c draw_skybox.c draw_texture.c init.c

#CC specifies which compiler we're using
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS_SDL2 = -I ./SDL2/include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS_SDL2 = -L ./SDL2/lib -l SDL2-2.0.0

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w #-Wl,-subsystem,windows

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = wolf3d

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS_SDL2) $(LIBRARY_PATHS_SDL2) $(COMPILER_FLAGS) -o $(OBJ_NAME)
