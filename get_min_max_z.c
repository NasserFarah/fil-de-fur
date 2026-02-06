/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_max_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:25:40 by fnasser           #+#    #+#             */
/*   Updated: 2025/11/02 17:15:04 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_min_max_z(t_map *map)
{
	ssize_t	i;
	ssize_t	j;

	if (!map)
		return ;
	map->min_z = map->map[0][0];
	map->max_z = map->map[0][0];
	i = 0;
	while (i < map->row)
	{
		j = 0;
		while (j < map->col)
		{
			if (map->map[i][j] < map->min_z)
				map->min_z = map->map[i][j];
			if (map->map[i][j] > map->max_z)
				map->max_z = map->map[i][j];
			j++;
		}
		i++;
	}
}
