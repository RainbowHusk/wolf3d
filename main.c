/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:19:54 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/22 00:19:56 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	quit(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->rend);
	sdl->rend = NULL;
	SDL_DestroyTexture(sdl->win_texture);
	sdl->win_texture = NULL;
	SDL_DestroyWindow(sdl->win);
	sdl->win = NULL;
	SDL_Quit();
}

void	hooks(t_sdl *sdl, t_map *map, t_player *player)
{
	float		tmp_x;
	float		tmp_y;

	while (SDL_PollEvent(&sdl->e) != 0)
	{
		if (sdl->e.type == SDL_QUIT)
			sdl->run = false;
		if (sdl->e.type == SDL_MOUSEMOTION)
		{
			if (sdl->e.motion.x - player->mouse_x > 0 || sdl->e.motion.x == W_W - 1)
				player->angle += 0.05;
			else
				player->angle -= 0.05;
			player->mouse_x = sdl->e.motion.x;
		}
		if (sdl->e.type == SDL_KEYDOWN)
		{
			if (sdl->e.key.keysym.sym == SDLK_ESCAPE)
				sdl->run = false;
			tmp_x = cos(player->angle) * player->speed;
			tmp_y = sin(player->angle) * player->speed;
			if (sdl->e.key.keysym.sym == SDLK_UP || sdl->e.key.keysym.sym == SDLK_w)
			{
				if ((map->map[
						((int)(player->x + tmp_x) / map->rect_w) + (int)(player->y + tmp_y) / map->rect_w * map->w
							]) == 0)
				{
					player->x += tmp_x;
					player->y += tmp_y;
				}
			}
			if (sdl->e.key.keysym.sym == SDLK_DOWN || sdl->e.key.keysym.sym == SDLK_s)
			{
				if ((map->map[
						((int)(player->x - tmp_x) / map->rect_w) + (int)(player->y - tmp_y) / map->rect_w * map->w
							]) == 0)
				{
					player->x -= tmp_x;
					player->y -= tmp_y;
				}
			}
			if (sdl->e.key.keysym.sym == SDLK_RIGHT || sdl->e.key.keysym.sym == SDLK_d)
			{
				if ((map->map[
						((int)(player->x - tmp_y) / map->rect_w) + (int)(player->y + tmp_x) / map->rect_w * map->w
							]) == 0)
				{
					player->x -= tmp_y;
					player->y += tmp_x;
				}
			}
			if (sdl->e.key.keysym.sym == SDLK_LEFT || sdl->e.key.keysym.sym == SDLK_a)
			{
				if ((map->map[
						((int)(player->x + tmp_y) / map->rect_w) + (int)(player->y - tmp_x) / map->rect_w * map->w
							]) == 0)
				{
					player->x += tmp_y;
					player->y -= tmp_x;
				}
			}
		}
	}
}

int		main(int arg, char **argv)
{
	t_main main;

	init(&main);
	while (main.sdl.run)
	{
		hooks(&main.sdl, &main.map, &main.player);
		SDL_LockTexture(main.sdl.win_texture, NULL, &main.sdl.bytes, &main.sdl.pitch);
		draw_skybox(&main.sdl, &main.player);
		draw_walls(&main, &main, &main.raycast, &main.map);
		draw_map(&main.map, &main.sdl);
		draw_fov(&main.sdl, &main.player);
		main.player.rect.x = main.player.x - 3;
		main.player.rect.y = main.player.y - 3;
		draw_rect(&main.sdl, &main.player.rect);
		SDL_UnlockTexture(main.sdl.win_texture);
		SDL_RenderCopy(main.sdl.rend, main.sdl.win_texture, NULL, NULL);
		SDL_RenderPresent(main.sdl.rend);
	}
	quit(&main.sdl);
	return (0);
}
