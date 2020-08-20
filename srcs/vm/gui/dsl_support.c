/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsl_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratardi <fratardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by fratardi          #+#    #+#             */
/*   Updated: 2020/06/19 15:37:18 by fratardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/vm.h"

void	cw_draw_cross(SDL_Rect *rect)
{
	SDL_RenderDrawLine(g_cwdata.gui->renderer, rect->x, rect->y
	+ (rect->h / 2), rect->x + rect->w, rect->y + (rect->h / 2));
	SDL_RenderDrawLine(g_cwdata.gui->renderer, rect->x, rect->y
	+ rect->h, rect->x + rect->w, rect->y);
	SDL_RenderDrawLine(g_cwdata.gui->renderer, rect->x, rect->y,
	rect->x + rect->w, rect->y + rect->h);
	SDL_RenderDrawLine(g_cwdata.gui->renderer, rect->x, rect->y
	+ (rect->h / 2), rect->x + rect->w, rect->y + (rect->h / 2));
	SDL_SetRenderDrawColor(g_cwdata.gui->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void	cw_clean_grid(void)
{
	if (g_cwdata.gui)
	{
		if (g_cwdata.gui->renderer)
			SDL_DestroyRenderer(g_cwdata.gui->renderer);
		if (g_cwdata.gui->window)
			SDL_DestroyWindow(g_cwdata.gui->window);
		ft_strdel((t_int8 **)&g_cwdata.gui->hex_str);
		free(g_cwdata.gui);
	}
	g_cwdata.gui = NULL;
	TTF_Quit();
	SDL_Quit();
}

char	*seg_hex_str(t_uint8 *src, t_uint8 *dst, t_uint32 start)
{
	static t_uint8	base[16] = "0123456789ABCDEF";
	t_int32			i;
	t_int32			j;

	ft_bzero(dst, 200);
	i = 0;
	j = 0;
	while (j < 64)
	{
		dst[i++] = base[(src[j + start] / 16) % 16];
		dst[i++] = base[src[j + start] % 16];
		dst[i++] = ' ';
		j++;
	}
	dst[i] = 0;
	return ((t_int8 *)dst);
}

void	cw_rect_init_sov(SDL_Rect *rect)
{
	rect->x = 0;
	rect->y = 4;
	rect->w = FONT_SIZE + 3;
	rect->h = FONT_SIZE - 1;
}

void	set_rect_info(SDL_Rect *rect, t_uint32 pos)
{
	rect->x += ((FONT_SIZE * 2) - 3) * (pos % 64);
	rect->y += FONT_SIZE * ((pos / 64) - 1) + FONT_SIZE;
	rect->w = FONT_SIZE + 3;
	rect->h = FONT_SIZE - 1;
}
