/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 19:53:21 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/21 19:53:22 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_skybox(t_sdl *sdl, t_player *player)
{
	int i;
	int j;
	int h;
	int a;

	a = 64 / PI;
	h = 2 * W_H / 3;
	i = -1;
	while (++i < W_W)
	{
		j = -1;
		while (++j < h)
		{
			sdl->y = (j * 64) / h;
			draw_texture(sdl, i, j, 128 + (int)(i +
				(player->angle * a)) / (W_W / 64) % 64);
		}
	}
}
