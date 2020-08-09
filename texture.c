#include "wolf3d.h"

void load_texture(t_textures *t)
{
    t->textures[0] = SDL_ConvertSurfaceFormat(SDL_LoadBMP("123.bmp"), SDL_PIXELFORMAT_ABGR8888, 0);
}