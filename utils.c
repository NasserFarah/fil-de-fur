/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:14:55 by fnasser           #+#    #+#             */
/*   Updated: 2025/11/03 16:22:44 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0)
		return ;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	matrix(t_parse *p, int fd, t_map *map)
{
	while (p->i < map->row)
	{
		p->line = get_next_line(fd);
		if (!p->line)
			break ;
		map = parse_line(p->line, map->col, map, p->i);
		free(p->line);
		if (!map->map[p->i] || !map->color[p->i])
		{
			free_map(*map);
			return ;
		}
		p->i++;
	}
}

int	check_fdf_file(char *c)
{
	int	len;
	int	dif;

	len = ft_strlen(c);
	dif = -1;
	if (len > 4)
		dif = ft_strncmp(".fdf", c + len - 4, 4);
	if (dif != 0)
		ft_printf("Wrong file! Please Try again!\n");
	return (dif);
}

void	alloc_map(t_map *map)
{
	map->map = (ssize_t **)malloc(map->row * sizeof(ssize_t *));
	map->color = (ssize_t **)malloc(map->row * sizeof(ssize_t *));
}

int	ft_count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}
