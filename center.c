/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:29:06 by fnasser           #+#    #+#             */
/*   Updated: 2025/11/09 20:57:19 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_top_left(t_point *p, t_center *dim, int scale)
{
	p->x = 0 * scale * 0.866;
	if (p->x < dim->min_x)
		dim->min_x = p->x;
	else
		dim->min_x = dim->min_x;
	if (p->x > dim->max_x)
		dim->max_x = p->x;
	else
		dim->max_x = dim->max_x;
	if (p->y < dim->min_y)
		dim->min_y = p->y;
	else
		dim->min_y = dim->min_y;
	if (p->y > dim->max_y)
		dim->max_y = p->y;
	else
		dim->max_y = dim->max_y;
}

void	center_top_right(t_point *p, t_map *map, t_center *dim, int scale)
{
	p->x = (map->col - 1 - 0) * scale * 0.866;
	p->y = (map->col - 1 + 0) * 0.5 * scale - map->min_z * scale;
	if (p->x < dim->min_x)
		dim->min_x = p->x;
	else
		dim->min_x = dim->min_x;
	if (p->x > dim->max_x)
		dim->max_x = p->x;
	else
		dim->max_x = dim->max_x;
	if (p->y < dim->min_y)
		dim->min_y = p->y;
	else
		dim->min_y = dim->min_y;
	if (p->y > dim->max_y)
		dim->max_y = p->y;
	else
		dim->max_y = dim->max_y;
}

void	center_bottom_left(t_point *p, t_center *dim, int scale, t_map *map)
{
	p->x = (0 - (map->row - 1)) * scale * 0.866;
	p->y = (0 + map->row - 1) * 0.5 * scale - map->min_z * scale;
	if (p->x < dim->min_x)
		dim->min_x = p->x;
	else
		dim->min_x = dim->min_x;
	if (p->x > dim->max_x)
		dim->max_x = p->x;
	else
		dim->max_x = dim->max_x;
	if (p->y < dim->min_y)
		dim->min_y = p->y;
	else
		dim->min_y = dim->min_y;
	if (p->y > dim->max_y)
		dim->max_y = p->y;
	else
		dim->max_y = dim->max_y;
}

void	center_bottom_right(t_point *p, t_center *dim, int scale, t_map *map)
{
	p->x = (map->col - 1 - (map->row - 1)) * scale * 0.866;
	p->y = (map->col - 1 + map->row - 1) * 0.5 * scale - map->min_z * scale;
	if (p->x < dim->min_x)
		dim->min_x = p->x;
	else
		dim->min_x = dim->min_x;
	if (p->x > dim->max_x)
		dim->max_x = p->x;
	else
		dim->max_x = dim->max_x;
	if (p->y < dim->min_y)
		dim->min_y = p->y;
	else
		dim->min_y = dim->min_y;
	if (p->y > dim->max_y)
		dim->max_y = p->y;
	else
		dim->max_y = dim->max_y;
}

void	center(t_map *map, int scale, int *off_x, int *off_y)
{
	t_center	dim;
	t_point		p;

	get_min_max_z(map);
	p.x = 0;
	p.y = 0;
	dim.min_x = 0;
	dim.max_x = 0;
	dim.min_y = -map->max_z * scale;
	dim.max_y = -map->max_z * scale;
	center_top_left(&p, &dim, scale);
	center_top_right(&p, map, &dim, scale);
	center_bottom_left(&p, &dim, scale, map);
	center_bottom_right(&p, &dim, scale, map);
	p.y = -map->max_z * scale;
	if (p.y < dim.min_y)
		dim.min_y = p.y;
	else
		dim.min_y = dim.min_y;
	*off_x = ((WIDTH - (dim.max_x - dim.min_x)) / 2 - dim.min_x);
	*off_y = ((HEIGHT - (dim.max_y - dim.min_y)) / 2 - dim.min_y) * 0.5;
}
