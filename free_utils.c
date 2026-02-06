/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:45:37 by fnasser           #+#    #+#             */
/*   Updated: 2025/10/22 17:45:47 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map map)
{
	ssize_t	i;

	if (!map.map)
		return ;
	i = 0;
	while (i < map.row)
	{
		free(map.map[i]);
		free(map.color[i]);
		i++;
	}
	free(map.map);
	free(map.color);
}

void	ft_free_split(char **splited)
{
	int	i;

	if (!splited)
		return ;
	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}
