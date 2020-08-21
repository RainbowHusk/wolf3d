/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:25:17 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/13 20:25:19 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	map_rect_w(t_map *map)
{
	int rect_w;
	int rect_h;

	rect_w = W_W / map->w / 3;
	rect_h = W_H / map->h / 3;
	if (rect_h < rect_w)
		map->rect_w = rect_h;
	else
		map->rect_w = rect_w;
}

void	draw_map(t_map *map, t_sdl *sdl)
{
	int y;
	int x;

	y = -1;
	while (++y < map->h)
	{
		x = -1;
		while (++x < map->w)
		{
			map->rect.x = x * map->rect_w;
			map->rect.y = y * map->rect_w;
			map->rect.h = map->rect_w;
			if (map->map[y * map->w + x] == 0)
				map->rect.color = RGB(20, 20, 20);
			if (map->map[y * map->w + x] == 1)
				map->rect.color = RGB(sdl->bytes_texture[0],
				sdl->bytes_texture[1], sdl->bytes_texture[2]);
			if (map->map[y * map->w + x] >= 2)
				map->rect.color = RGB(sdl->bytes_texture[0],
				sdl->bytes_texture[64 * 1], sdl->bytes_texture[64 * 2]);
			draw_rect(sdl, &map->rect);
		}
	}
}
