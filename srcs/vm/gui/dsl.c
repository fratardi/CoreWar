/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratardi <fratardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by fratardi          #+#    #+#             */
/*   Updated: 2020/07/02 01:11:47 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/vm.h"

void	dsl_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	g_cwdata.gui = ft_memalloc(sizeof(t_cw_gui));
	g_cwdata.gui->window =
	SDL_CreateWindow("Corewar By Scoron, Tpacaud & Fratardi",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H,
		SDL_WINDOW_RESIZABLE);
	g_cwdata.gui->renderer = SDL_CreateRenderer(g_cwdata.gui->window, -1, 0);
	if (!(g_cwdata.gui->font =
			TTF_OpenFont("Framework/TTF/Medium.ttf", FONT_SIZE)))
		cw_exit(0, 0, "ERROR_NO_FONT");
	SDL_SetRenderDrawColor(g_cwdata.gui->renderer, 0x3F, 0x3F, 0x3F, 255);
	SDL_RenderClear(g_cwdata.gui->renderer);
	if (!(g_cwdata.gui->hex_str =
			(t_uint8 *)ft_memalloc(sizeof(t_uint8) * 200)))
		cw_exit(0, 0, "error malloc");
}

void	cw_query_texture(t_uint32 line_index,
		SDL_Surface *surface, SDL_Texture *texture)
{
	t_int32		tex_w;
	t_int32		tex_h;
	SDL_Rect	dstrect;

	tex_w = 0;
	tex_h = 0;
	SDL_QueryTexture(texture, NULL, NULL, &tex_w, &tex_h);
	dstrect.x = 0;
	dstrect.y = line_index * FONT_SIZE + 2;
	dstrect.w = tex_w;
	dstrect.h = tex_h;
	SDL_RenderCopy(g_cwdata.gui->renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void	cw_dump_line(t_uint32 line_index)
{
	char		*str;
	SDL_Color	color;
	SDL_Surface	*surface;
	SDL_Texture	*texture;

	color.r = 255;
	color.g = 255;
	color.a = 255;
	color.b = 255;
	str = seg_hex_str(g_cwdata.memory, g_cwdata.gui->hex_str, line_index * 64);
	surface = TTF_RenderText_Solid(g_cwdata.gui->font, str, color);
	texture = SDL_CreateTextureFromSurface(g_cwdata.gui->renderer, surface);
	cw_query_texture(line_index, surface, texture);
}

void	cw_print_grid(void)
{
	t_int32		check;
	t_uint32	i;
	SDL_Event	event;

	i = 0;
	cw_draw_sov();
	while (i < 64)
		cw_dump_line(i++);
	SDL_RenderPresent(g_cwdata.gui->renderer);
	check = 1;
	while (check)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
			check = 0;
		else if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			cw_exit(FAILED, 0, "Error : You closed the GUI");
	}
	SDL_SetRenderDrawColor(g_cwdata.gui->renderer, 0x3F, 0x3F, 0x3F, 255);
	SDL_RenderClear(g_cwdata.gui->renderer);
}
