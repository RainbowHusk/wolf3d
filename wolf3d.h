#ifndef WOLF3D_H
# define WOLF3D_H

#include "SDL2/include/SDL.h"
#include <stdbool.h>
#include <stdio.h>
#define PI 3.14
#define W_W 512 //1366
#define W_H 512 //768
#define RGB(r, g, b) r + (g << 8) + (b << 16)
#define FOV PI/3

typedef struct s_sdl
{
	SDL_Surface *scrs;
	SDL_Surface *textures;
	SDL_Renderer *rend;
	SDL_Window *win;
	SDL_Texture *win_texture;
	SDL_Event e;
	unsigned char *bytes;
	unsigned char *bytes_texture;
	int pitch;
	bool run;
} t_sdl;

typedef struct s_map
{
	int h;
	int w;
	int s;
	int rect_w;
	int *map;
} t_map;

typedef struct s_textures
{
	SDL_Surface *textures[6];
} t_textures;

typedef struct s_player
{
	float angle;
	float x;
	float y;
} t_player;


#endif