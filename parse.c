/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:13:27 by fnasser           #+#    #+#             */
/*   Updated: 2025/11/03 16:05:12 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_color_matrix(char *splited)
{
	int	i;
	int	color;

	i = 0;
	if (!splited)
		return (0xFFFFFF);
	while (splited[i] != '\0')
	{
		while (splited[i] >= 48 && splited[i] <= 57)
			i++;
		if (splited[i] == ',')
		{
			i++;
			if (splited[i] == '0' && (splited[i + 1] == 'x'
					|| splited[i + 1] == 'X'))
			{
				color = from_hex_to_int(&splited[i]);
				return (color & 0xFFFFFF);
			}
		}
		if (splited[i] != 0)
			i++;
	}
	return (0xFFFFFF);
}

t_map	*parse_line(char *line, int col, t_map *map, ssize_t index)
{
	ssize_t		i;
	char		**splited;

	splited = ft_split(line, ' ');
	if (!splited)
		return (NULL);
	map->map[index] = (ssize_t *)malloc(col * sizeof(ssize_t));
	map->color[index] = (ssize_t *)malloc(col * sizeof(ssize_t));
	if (!map->map[index] || !map->color[index])
	{
		ft_free_split(splited);
		return (free(map->map[index]), free(map->color[index]), NULL);
	}
	i = 0;
	while (i < col && splited[i])
	{
		map->map[index][i] = ft_atoi(splited[i]);
		map->color[index][i] = ft_color_matrix(splited[i]);
		i++;
	}
	ft_free_split(splited);
	return (map);
}

ssize_t	get_map_rows(t_map *map, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	map->row = ft_count_lines(fd);
	close(fd);
	return (map->row);
}

int	get_matrix_dimensions(t_map *map, char *file, int fd, char **line)
{
	*line = get_next_line(fd);
	if (!*line)
		return (0);
	map->col = ft_word_count(*line);
	free(*line);
	*line = get_next_line(fd);
	while (*line)
	{
		free(*line);
		*line = get_next_line(fd);
	}
	close(fd);
	map->row = get_map_rows(map, file);
	if (map->row == -1)
		return (0);
	return (1);
}

t_map	parse_map(int fd, t_map *map, char *file)
{
	t_parse	p;

	p.i = 0;
	p.dim = get_matrix_dimensions(map, file, fd, &p.line);
	if (!p.dim)
		return (*map);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (*map);
	}
	alloc_map(map);
	if (!map->map || !map->color)
		return (*map);
	matrix(&p, fd, map);
	close(fd);
	return (*map);
}
