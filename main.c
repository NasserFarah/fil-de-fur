/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:07:16 by fnasser           #+#    #+#             */
/*   Updated: 2025/10/22 18:28:08 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_fdf(t_map *map)
{
	t_win	win;

	win.mlx = mlx_init();
	if (win.mlx == NULL)
		return ;
	win.window = mlx_new_window(win.mlx, WIDTH, HEIGHT, "Fil De Fer");
	if (win.window == NULL)
		return (free(win.mlx));
	win.map = map;
	win.zoom = 1;
	win.off_x = 0;
	win.off_y = 0;
	initialize_img(&win, WIDTH, HEIGHT);
	mlx_loop_hook(win.mlx, handle_output, &win);
	mlx_key_hook(win.window, handle_keypress, &win);
	mlx_mouse_hook(win.window, zoom, &win);
	mlx_hook(win.window, 17, 0, cross, &win);
	mlx_loop(win.mlx);
}

int	main(int ac, char **av)
{
	int		fd;
	int		i;
	t_map	map;

	i = 0;
	if (ac == 2)
	{
		if (check_fdf_file(av[1]) != 0)
			return (1);
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			return (1);
		}
		map.map = NULL;
		map = parse_map(fd, &map, av[1]);
		if (map.map)
			init_fdf(&map);
		free_map(map);
		close(fd);
	}
	else
		ft_printf("Wrong number of arguments! Please try again.\n");
	return (0);
}
