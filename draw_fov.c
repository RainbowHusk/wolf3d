/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:02:12 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/13 20:02:14 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_fov(t_sdl *sdl, t_player *player)
{
	float angle;
	float cx;
	float cy;
	float t;

	t = 0;
	angle = player->angle - FOV / 2;
	while (t < 20)
	{
		cx = player->x + t * cos(angle);
		cy = player->y + t * sin(angle);
		if (cx >= W_W || cy >= W_H || cx < 0 || cy < 0)
			break ;
		input_pixel(sdl, cx, cy, RGB(128, 128, 128));
		cx = player->x + t * cos(angle + FOV);
		cy = player->y + t * sin(angle + FOV);
		if (cx >= W_W || cy >= W_H || cx < 0 || cy < 0)
			break ;
		input_pixel(sdl, cx, cy, RGB(128, 128, 128));
		t += .1;
	}
}
