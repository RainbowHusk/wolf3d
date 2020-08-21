/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 19:54:06 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/21 19:54:08 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_texture(t_sdl *sdl, int x, int y, int xt)
{
	sdl->bytes[x * 4 + 0 + y * sdl->pitch] =
		sdl->bytes_texture[xt * 4 + 0 + sdl->y * sdl->textures->pitch];
	sdl->bytes[x * 4 + 1 + y * sdl->pitch] =
		sdl->bytes_texture[xt * 4 + 1 + sdl->y * sdl->textures->pitch];
	sdl->bytes[x * 4 + 2 + y * sdl->pitch] =
		sdl->bytes_texture[xt * 4 + 2 + sdl->y * sdl->textures->pitch];
}
