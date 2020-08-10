#include "wolf3d.h"

int init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return 1;
	sdl->win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_W, W_H, SDL_WINDOW_SHOWN);
	if (sdl->win == NULL)
		return 1;
	sdl->rend = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	if (sdl->rend == NULL)
		return 1;
	sdl->textures = SDL_ConvertSurfaceFormat(SDL_LoadBMP("123.bmp"), SDL_PIXELFORMAT_ABGR8888, 0);
	sdl->bytes_texture = (unsigned char*) sdl->textures->pixels;
	sdl->win_texture = SDL_CreateTexture(sdl->rend, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, W_W, W_H);
	sdl->scrs = SDL_GetWindowSurface(sdl->win);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl->run = true;
	return 0;
}

void quit(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->rend);
	sdl->rend = NULL;
	SDL_DestroyTexture(sdl->win_texture);
	sdl->win_texture = NULL;
	SDL_DestroyWindow(sdl->win);
	sdl->win = NULL;
	SDL_Quit();
}

void input_pixel(t_sdl *sdl, int x, int y, int color)
{
	sdl->bytes[x * 4 + 0 + y * sdl->pitch] = (color & 0xFF);
	sdl->bytes[x * 4 + 1 + y * sdl->pitch] = (color & 0xFF00) >> 8;
	sdl->bytes[x * 4 + 2 + y * sdl->pitch] = (color & 0xFF0000) >> 16;
	sdl->bytes[x * 4 + 3 + y * sdl->pitch] = 0;
}

void draw_rect(t_sdl *sdl, int x, int y, int h, int color)
{
	int i;
	int j;

	i = y - 1;
	while (++i < y + h)
	{
		j = x - 1;
		while (++j < x + h)
		{
			if (j >= W_W || i >= W_H || j < 0 || i < 0)
				continue;
			input_pixel(sdl, j, i, color);
		}
	}
}

void draw_fov(t_sdl *sdl, t_player *player)
{
    float angle1;
	float angle2;
	float t;

	t = 0;
	angle2 = player->angle - FOV / 2 + FOV;
	angle1 = player->angle - FOV / 2;
	while (t < 20)
	{
        float cx1 = player->x + t * cos(angle1);
        float cy1 = player->y + t * sin(angle1);
		float cx2 = player->x + t * cos(angle2);
        float cy2 = player->y + t * sin(angle2);
		if (cx1 >= W_W || cy1 >= W_H || cx1 < 0 || cy1 < 0)
			break;
		if (cx2 >= W_W || cy2 >= W_H || cx2 < 0 || cy2 < 0)
			break;
		input_pixel(sdl, cx1, cy1, RGB(128, 128, 128));
		input_pixel(sdl, cx2, cy2, RGB(128, 128, 128));
		t += .05;
	}
}

void draw_texture(t_sdl *sdl, int x, int y, int xt, int yt)
{
	sdl->bytes[x * 4 + 0 + y * sdl->pitch] = sdl->bytes_texture[xt * 4 + 0 + yt * sdl->textures->pitch];
	sdl->bytes[x * 4 + 1 + y * sdl->pitch] = sdl->bytes_texture[xt * 4 + 1 + yt * sdl->textures->pitch];
	sdl->bytes[x * 4 + 2 + y * sdl->pitch] = sdl->bytes_texture[xt * 4 + 2 + yt * sdl->textures->pitch];
	// *(int *)(sdl->bytes + x * 4 + y * sdl->pitch) = *(int *)(sdl->bytes_texture + xt * 4 + 0 + yt * sdl->textures->pitch);
}

void draw_walls(t_map *map, t_sdl *sdl, t_player *player)
{
	int i;
	int j;
	float t;

	i = -1;
	while (++i < W_W)
	{
        float angle = player->angle - FOV / 2 + FOV * i / W_W;
		t = 0;
		while (t < W_W)
		{
        	float cx = player->x + t * cos(angle);
        	float cy = player->y + t * sin(angle);
			if (map->map[(int)cx / map->rect_w + (int)cy / map->rect_w * map->w] != 0 )
			{
				int column_height = W_H / (t * cos(angle - player->angle)) * map->rect_w;
				float hitx = cx / map->rect_w - floor((cx / map->rect_w)+.5);
				float hity = cy / map->rect_w - floor((cy / map->rect_w)+.5);
				int x_texcoord = hitx * 64;
				if (fabs(hity) > fabs(hitx))
					x_texcoord = hity * 64;
				if (x_texcoord < 0)
					x_texcoord += 64;
				j = -1;
                while (++j < column_height)
				{
					int pix = j + W_H / 2 - column_height / 2;
                    if (pix < 0 || pix >= W_H) continue;
					if (map->map[(int)cx / map->rect_w + (int)cy / map->rect_w * map->w] == 1)
						draw_texture(sdl, i, pix, x_texcoord, (j * 64) / column_height);
					else if (map->map[(int)cx / map->rect_w + (int)cy / map->rect_w * map->w] == 2 )
						draw_texture(sdl, i, pix, 64 + x_texcoord, (j * 64) / column_height);
                }
                break;
			}
			t += .05;
		}
	}
}

void map_rect_w(t_map *map)
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

void draw_map(t_map *map, t_sdl *sdl)
{
	int y;
	int x;

	y = -1;
	x = -1;
	while (++y < map->h)
	{
		while (++x < map->w)
		{
			if (map->map[y * map->w + x] == 0)
				draw_rect(sdl, x * map->rect_w, y * map->rect_w, map->rect_w, RGB(20, 20, 20));
			else if (map->map[y * map->w + x] == 1)
				draw_rect(sdl, x * map->rect_w, y * map->rect_w, map->rect_w, RGB(sdl->bytes_texture[0], sdl->bytes_texture[1], sdl->bytes_texture[2]));
			else if (map->map[y * map->w + x] == 2)
				draw_rect(sdl, x * map->rect_w, y * map->rect_w, map->rect_w, RGB(sdl->bytes_texture[0], sdl->bytes_texture[64*1], sdl->bytes_texture[64*2]));
		}
		x = -1;
	}
}

int main(int arg, char **argv)
{
	t_sdl sdl;
	t_player p;
	t_map map;
	int x = -1, y = -1, spd = 3;

	map.w = 8;
	map.h = 8;
	map.s = map.w * map.h;
	map.map = (int *)malloc(sizeof(int) * map.s);
	while (++y < map.h)
	{
		while (++x < map.w)
			if (x == 0 || y == 0 || x == map.w - 1 || y == map.h - 1)
				map.map[y * map.w + x] = 1;
			else
				map.map[y * map.w + x] = 0;
		x = -1;
	}
	map.map[1 * map.w + 3] = 1;
	map.map[2 * map.w + 3] = 2;
	map.map[5 * map.w + 5] = 2;
	x = 0;
	p.x = 50;
	p.y = 50;
	p.angle = 4.72;
	if (init(&sdl))
		return 1;
	while (sdl.run)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = false;
			if (sdl.e.type == SDL_MOUSEMOTION)
			{
				if (sdl.e.motion.x - x > 0 || sdl.e.motion.x == W_W - 1)
					p.angle += 0.01;
				else
					p.angle -= 0.01;
				if (p.angle > PI * 2)
					p.angle -= PI * 2;
				else if (p.angle < 0)
					p.angle += PI * 2;
				x = sdl.e.motion.x;
			}
			if (sdl.e.type == SDL_KEYDOWN)
			{
				if (sdl.e.key.keysym.sym == SDLK_ESCAPE)
					sdl.run = false;
				float tmpx = cos(p.angle) * spd;
				float tmpy = sin(p.angle) * spd;
				if (sdl.e.key.keysym.sym == SDLK_UP || sdl.e.key.keysym.sym == SDLK_w)
				{
					if ((map.map[
							((int)(p.x + tmpx)/map.rect_w) + (int)(p.y + tmpy)/map.rect_w * map.w
								]) == 0)
					{
						p.x += tmpx;
						p.y += tmpy;
					}
				}
				if (sdl.e.key.keysym.sym == SDLK_DOWN || sdl.e.key.keysym.sym == SDLK_s)
				{
					if ((map.map[
							((int)(p.x - tmpx)/map.rect_w) + (int)(p.y - tmpy)/map.rect_w * map.w
								]) == 0)
					{
						p.x -= tmpx;
						p.y -= tmpy;
					}
				}
				if (sdl.e.key.keysym.sym == SDLK_RIGHT || sdl.e.key.keysym.sym == SDLK_d)
				{
					if ((map.map[
							((int)(p.x - tmpy)/map.rect_w) + (int)(p.y + tmpx)/map.rect_w * map.w
								]) == 0)
					{
						p.x -= tmpy;
						p.y += tmpx;
					}
				}
				if (sdl.e.key.keysym.sym == SDLK_LEFT || sdl.e.key.keysym.sym == SDLK_a)
				{
					if ((map.map[
							((int)(p.x + tmpy)/map.rect_w) + (int)(p.y - tmpx)/map.rect_w * map.w
								]) == 0)
					{
						p.x += tmpy;
						p.y -= tmpx;
					}
				}
			}
		}
		SDL_LockTexture(sdl.win_texture, NULL, &sdl.bytes, &sdl.pitch);
		draw_rect(&sdl, 0, 0, W_W, RGB(0, 0, 0));
		map_rect_w(&map);
		draw_walls(&map, &sdl, &p);
		draw_map(&map, &sdl);
		draw_fov(&sdl, &p);
		draw_rect(&sdl, p.x - 3, p.y - 3, 6, RGB(255, 255, 255));
		SDL_UnlockTexture(sdl.win_texture);
		SDL_RenderCopy(sdl.rend, sdl.win_texture, NULL, NULL);
		SDL_RenderPresent(sdl.rend);
	}
	quit(&sdl);
	return 0;
}