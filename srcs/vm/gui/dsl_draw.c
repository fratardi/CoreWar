/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratardi <fratardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by fratardi          #+#    #+#             */
/*   Updated: 2020/06/19 15:37:18 by fratardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/vm.h"

void	cw_set_sov_color(t_uint32 col, t_uint32 line, SDL_Color *color)
{
	t_uint32 tab[7];
	t_uint32 cowl;

	tab[0] = 0xFFF3F000;
	tab[1] = 0x00fbff00;
	tab[2] = 0x04F06A00;
	tab[3] = 0xa0519500;
	tab[4] = 0xd45087;
	cowl = tab[(g_cwdata.colors[(col + (line * 64)) % MEM_SIZE] % 4)];
	if (!g_cwdata.colors[(col + (line * 64)) % MEM_SIZE])
		cowl = 0;
	color->r = ((cowl & 0xFF000000) >> 24);
	color->g = ((cowl & 0x00FF0000) >> 16);
	color->b = ((cowl & 0x0000FF00) >> 8);
	color->a = SDL_ALPHA_OPAQUE;
}

void	cw_set_proc_color(t_int32 *i)
{
	t_uint32	tab[7];
	SDL_Color	color;

	tab[0] = 0xFFF3F000;
	tab[1] = 0x00fbff00;
	tab[2] = 0x04F06A00;
	tab[3] = 0xa0519500;
	tab[4] = 0xd4508700;
	tab[5] = 0xd4508700;
	if (*i > 4)
		SDL_SetRenderDrawColor(g_cwdata.gui->renderer,
				0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	else
	{
		color.r = ((tab[*i % 4] & 0xFF000000) >> 24);
		color.g = ((tab[*i % 4] & 0x00FF0000) >> 16);
		color.b = ((tab[*i % 4] & 0x0000FF00) >> 8);
		color.a = SDL_ALPHA_OPAQUE;
		SDL_SetRenderDrawColor(g_cwdata.gui->renderer,
				color.r, color.g, color.b, color.a);
	}
}

void	cw_draw_procs(SDL_Rect *rect)
{
	t_cw_proc	*list;
	t_int32		i;

	list = g_cwdata.first_proc;
	i = 0;
	while (list != NULL)
	{
		cw_rect_init_sov(rect);
		set_rect_info(rect, (&list->pos[0] - &g_cwdata.memory[0]));
		cw_set_proc_color(&i);
		cw_draw_cross(rect);
		SDL_SetRenderDrawColor(g_cwdata.gui->renderer,
				0, 0, 0, SDL_ALPHA_OPAQUE);
		list = list->next;
		i++;
	}
}

void	cw_draw_frame(SDL_Rect *rect)
{
	SDL_RenderDrawLine(g_cwdata.gui->renderer, rect->x,
			rect->y, rect->x + rect->w, rect->y);
	SDL_RenderDrawLine(g_cwdata.gui->renderer, rect->x, rect->y
		+ rect->h, rect->x + rect->w, rect->y + rect->h);
	SDL_RenderDrawLine(g_cwdata.gui->renderer, rect->x,
			rect->y, rect->x, rect->y + rect->h);
	SDL_RenderDrawLine(g_cwdata.gui->renderer, rect->x + rect->w,
			rect->y, rect->x + rect->w, rect->y + rect->h);
	SDL_SetRenderDrawColor(g_cwdata.gui->renderer,
			0, 0, 0, SDL_ALPHA_OPAQUE);
}

void	cw_draw_sov(void)
{
	SDL_Rect	rect;
	SDL_Color	color;
	t_uint32	i;
	t_uint32	j;

	cw_rect_init_sov(&rect);
	cw_draw_procs(&rect);
	cw_rect_init_sov(&rect);
	j = 0;
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{
			cw_set_sov_color(i++, j, &color);
			SDL_SetRenderDrawColor(g_cwdata.gui->renderer,
					color.r, color.g, color.b, color.a);
			cw_draw_frame(&rect);
			rect.x += FONT_SIZE * 2;
			rect.x -= 3;
		}
		rect.x = 0;
		rect.y += FONT_SIZE;
		j++;
	}
}
