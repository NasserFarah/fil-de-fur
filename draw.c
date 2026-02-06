/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:08:34 by fnasser           #+#    #+#             */
/*   Updated: 2025/10/22 15:17:58 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_next(t_wireframe *wire, t_win *win)
{
	t_wireframe	temp;

	temp = *wire;
	temp.x = wire->x + 1;
	wire->next = project(&temp, win->map->map);
	wire->next.color = win->map->color[wire->y][wire->x + 1];
	put_line(&win->image, wire->curr, wire->next);
}

void	draw_down(t_wireframe *wire, t_win *win)
{
	t_wireframe	temp;

	temp = *wire;
	temp.y = wire->y + 1;
	wire->down = project(&temp, win->map->map);
	wire->down.color = win->map->color[wire->y + 1][wire->x];
	put_line(&win->image, wire->curr, wire->down);
}

void	draw_lines(t_win *win, t_wireframe *wire)
{
	while (wire->y < win->map->row)
	{
		wire->x = 0;
		while (wire->x < win->map->col)
		{
			wire->curr = project(wire, win->map->map);
			wire->curr.color = win->map->color[wire->y][wire->x];
			if (wire->y == win->map->row - 1 && wire->x == win->map->col - 1)
				break ;
			if (wire->x < win->map->col - 1)
				draw_next(wire, win);
			if (wire->y < win->map->row - 1)
				draw_down(wire, win);
			wire->x++;
		}
		wire->y++;
	}
}
