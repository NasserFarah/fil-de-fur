/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:52:38 by fnasser           #+#    #+#             */
/*   Updated: 2025/10/22 16:08:08 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	scale(t_map *map)
{
	int	z_range;
	int	scale_x;
	int	scale_y;
	int	scale;

	get_min_max_z(map);
	z_range = map->max_z - map->min_z;
	scale_x = (WIDTH) * 1.2 / ((map->col - 1 + map->row - 1) * 0.866);
	scale_y = (HEIGHT) * 1.2 / ((map->col - 1 + map->row - 1) * 0.5 + z_range);
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 1)
		scale = 1;
	return (scale);
}

t_point	project(t_wireframe *w, ssize_t **map)
{
	t_point	p;

	p.x = ((w->x - w->y) * w->scale * 0.866 * w->zoom) + (w->off_x);
	p.y = (((w->x + w->y) * 0.5 - map[w->y][w->x] * 0.5)
			* w->scale * w->zoom) + (w->off_y);
	return (p);
}

void	init_direction(t_line *line, t_point f, t_point l)
{
	line->delta_x = labs(l.x - f.x);
	line->delta_y = labs(l.y - f.y);
	if (f.x < l.x)
		line->direction_x = 1;
	else
		line->direction_x = -1;
	if (f.y < l.y)
		line->direction_y = 1;
	else
		line->direction_y = -1;
	line->error = line->delta_x - line->delta_y;
}
