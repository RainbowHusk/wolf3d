/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:11:33 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/13 20:11:34 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_rect(t_sdl *sdl, t_rect *rect)
{
	int i;
	int j;

	i = rect->y - 1;
	while (++i < rect->y + rect->h)
	{
		j = rect->x - 1;
		while (++j < rect->x + rect->h)
		{
			if (j >= W_W || i >= W_H || j < 0 || i < 0)
				continue;
			input_pixel(sdl, j, i, rect->color);
		}
	}
}
