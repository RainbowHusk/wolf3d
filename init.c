/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:30:46 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/22 00:30:47 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		init_sdl(t_sdl *sdl)
{
	SDL_Surface *pic;

	pic = SDL_LoadBMP("123.bmp");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (1);
	sdl->win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, W_W, W_H, SDL_WINDOW_SHOWN);
	if (sdl->win == NULL)
		return (1);
	sdl->rend = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	if (sdl->rend == NULL)
		return (1);
	sdl->textures = SDL_ConvertSurfaceFormat(pic, SDL_PIXELFORMAT_ABGR8888, 0);
	sdl->bytes_texture = (unsigned char*)sdl->textures->pixels;
	sdl->win_texture = SDL_CreateTexture(sdl->rend,
		SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, W_W, W_H);
	sdl->scrs = SDL_GetWindowSurface(sdl->win);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl->run = true;
	return (0);
}

void	init_map(t_map *map)
{
	int y;
	int x;

	map->w = 8;
	map->h = 8;
	map->map = (int *)malloc(sizeof(int) * (map->w * map->h));
	y = -1;
	while (++y < map->h)
	{
		x = -1;
		while (++x < map->w)
			if (x == 0 || y == 0 || x == map->w - 1 || y == map->h - 1)
				map->map[y * map->w + x] = 1;
			else
				map->map[y * map->w + x] = 0;
	}
	map_rect_w(map);
	map->map[1 * map->w + 3] = 5;
	map->map[2 * map->w + 3] = 2;
	map->map[5 * map->w + 5] = 2;
}

void	init_player(t_player *player)
{
	player->x = 100;
	player->y = 100;
	player->angle = 2121;
	player->speed = 3;
	player->mouse_x = 0;
	player->rect.h = 6;
	player->rect.color = RGB(255, 255, 255);
}

void	init(t_main *main)
{
	init_map(&main->map);
	init_player(&main->player);
	init_sdl(&main->sdl);
}
