/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:01:37 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/13 20:01:39 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	input_pixel(t_sdl *sdl, int x, int y, int color)
{
	sdl->bytes[x * 4 + 0 + y * sdl->pitch] = (color & 0xFF);
	sdl->bytes[x * 4 + 1 + y * sdl->pitch] = (color & 0xFF00) >> 8;
	sdl->bytes[x * 4 + 2 + y * sdl->pitch] = (color & 0xFF0000) >> 16;
	sdl->bytes[x * 4 + 3 + y * sdl->pitch] = 0;
}
