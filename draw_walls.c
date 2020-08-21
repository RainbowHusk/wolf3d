/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:08:57 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/13 20:08:59 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_xcoord(int *x, float hitx, float hity)
{
	*x = hitx * 64;
	if (fabs(hity) > fabs(hitx))
		*x = hity * 64;
	if (*x < 0)
		*x += 64;
}

int		draw_column(t_main *main, t_map *map, int x, int column_h)
{
	float	hitx;
	float	hity;
	int		x_texture;
	int		j;
	int		y;

	hitx = main->raycast.x - floorf(main->raycast.x + .5);
	hity = main->raycast.y - floorf(main->raycast.y + .5);
	init_xcoord(&x_texture, hitx, hity);
	j = -1;
	while (++j < column_h)
	{
		y = j + W_H / 2 - column_h / 2;
		main->sdl.y = (j * 64) / column_h;
		if (y < 0 || y >= W_H)
			continue;
		if (map->map[(int)main->raycast.x + (int)main->raycast.y * map->w] == 1)
			draw_texture(&main->sdl, x, y, x_texture);
		if (map->map[(int)main->raycast.x + (int)main->raycast.y * map->w] >= 2)
			draw_texture(&main->sdl, x, y, 64 + x_texture);
	}
	return (y);
}

void	draw_floor(t_sdl *sdl, int x, int y)
{
	while (++y < W_H)
		input_pixel(sdl, x, y, RGB(113, 113, 113));
}

void	draw_walls(t_main *main, t_player *player,
					t_raycast *raycast, t_map *map)
{
	int		i;
	float	t;
	float	angle;

	i = -1;
	while (++i < W_W)
	{
		angle = player->angle - FOV / 2 + FOV * i / W_W;
		t = 0;
		while (t < W_W)
		{
			raycast->x = (player->x + t * cos(angle)) / main->map.rect_w;
			raycast->y = (player->y + t * sin(angle)) / main->map.rect_w;
			if (map->map[(int)raycast->x + (int)raycast->y * map->w] != 0)
			{
				draw_floor(&main->sdl, i, draw_column(main, map, i, W_H /
					(t * cos(angle - player->angle)) * map->rect_w));
				break ;
			}
			t += .05;
		}
	}
}
