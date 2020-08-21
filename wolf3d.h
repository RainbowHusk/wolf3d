/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:15:20 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/13 20:15:24 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "SDL2/include/SDL2/SDL.h"
# include <stdbool.h>
# include <stdio.h>
# define PI 3.14
# define W_W 512
# define W_H 512
# define RGB(r, g, b) r + (g << 8) + (b << 16)
# define FOV PI/3

typedef struct		s_raycast
{
	float			x;
	float			y;
}					t_raycast;

typedef struct		s_rect
{
	int				x;
	int				y;
	int				h;
	int				color;
}					t_rect;

typedef struct		s_player
{
	float			angle;
	float			x;
	float			y;
	int				speed;
	int				mouse_x;
	t_rect			rect;
}					t_player;

typedef struct		s_map
{
	int				h;
	int				w;
	int				rect_w;
	int				*map;
	t_rect			rect;
}					t_map;

typedef struct		s_sdl
{
	SDL_Surface		*scrs;
	SDL_Surface		*textures;
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_texture;
	SDL_Event		e;
	int				y;
	unsigned char	*bytes;
	unsigned char	*bytes_texture;
	int				pitch;
	bool			run;
}					t_sdl;

typedef struct		s_main
{
	t_player		player;
	t_map			map;
	t_sdl			sdl;
	t_raycast		raycast;
	t_rect			rect;
}					t_main;

void				draw_map(t_map *map, t_sdl *sdl);
void				draw_fov(t_sdl *sdl, t_player *player);
void				draw_rect(t_sdl *sdl, t_rect *rect);
void				draw_walls(t_main *main, t_player *player, t_raycast *raycast, t_map *map);
void				input_pixel(t_sdl *sdl, int x, int y, int color);
void				map_rect_w(t_map *map);
void				draw_texture(t_sdl *sdl, int x, int y, int xt);
void				draw_skybox(t_sdl *sdl, t_player *player);
void				init(t_main *main);

#endif
