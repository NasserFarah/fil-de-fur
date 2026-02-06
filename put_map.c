/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:26:50 by fnasser           #+#    #+#             */
/*   Updated: 2025/10/22 16:07:25 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_line(t_image *img, t_point f, t_point l)
{
	t_line	line;

	if (!img)
		return ;
	init_direction(&line, f, l);
	if (f.color == l.color)
	{
		while (102)
		{
			put_line_same_color(img, &f, l, &line);
			if (f.x == l.x && f.y == l.y)
				break ;
		}
	}
	else if (f.color != l.color)
		put_line_diff_color(img, f, l, &line);
}

void	put_line_same_color(t_image *img, t_point *f, t_point l, t_line *line)
{
	if (f->x >= 0 && f->x < img->width && f->y >= 0 && f->y < img->height)
		img_pix_put(img, f->x, f->y, f->color);
	if ((2 * line->error) > (-1 * line->delta_y))
	{
		line->error -= line->delta_y;
		f->x += line->direction_x;
	}
	else if ((2 * line->error) < line->delta_x)
	{
		line->error += line->delta_x;
		f->y += line->direction_y;
	}
	(void)l;
}

void	put_line_diff_color(t_image *img, t_point f, t_point l, t_line *line)
{
	t_color	clr;
	int		total_steps;
	int		current_step;

	total_steps = line->delta_x + line->delta_y;
	current_step = 0;
	while (102)
	{
		clr.t = (float)(current_step) / (float)(total_steps * 25);
		clr.r = (f.color >> 16 & 0xFF)
			+ ((l.color >> 16 & 0xFF) - (f.color >> 16 & 0xFF)) * clr.t;
		clr.g = (f.color >> 8 & 0xFF)
			+ ((l.color >> 8 & 0xFF) - (f.color >> 8 & 0xFF)) * clr.t;
		clr.b = (f.color & 0xFF) + ((l.color & 0xFF) - (f.color & 0xFF))
			* clr.t;
		f.color = (clr.r << 16) | (clr.g << 8) | (clr.b);
		put_line_same_color(img, &f, l, line);
		if (f.x == l.x && f.y == l.y)
			break ;
		current_step++;
		total_steps--;
	}
}

void	put_map(t_win *win)
{
	t_wireframe	*wire;

	wire = (t_wireframe *)malloc(sizeof(t_wireframe));
	if (!wire)
		return ;
	wire->scale = scale(win->map);
	center(win->map, wire->scale, &wire->off_x, &wire->off_y);
	wire->y = 0;
	wire->off_x = wire->off_x * win->zoom + win->off_x;
	wire->off_y = wire->off_y * win->zoom + win->off_y;
	wire->zoom = win->zoom;
	draw_lines(win, wire);
	free(wire);
}
