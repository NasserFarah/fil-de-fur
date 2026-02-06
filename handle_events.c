/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:50:25 by fnasser           #+#    #+#             */
/*   Updated: 2025/10/28 18:21:33 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoom(int button, int x, int y, t_win *win)
{
	float	zooming_value;
	float	img_x;
	float	img_y;

	zooming_value = 0.0;
	if (button == 4 || button == 5)
	{
		if (button == 4)
			zooming_value = 1.1;
		if (button == 5)
			zooming_value = 0.9;
		img_x = (x - win->off_x) / win->zoom;
		img_y = (y - win->off_y) / win->zoom;
		win->zoom *= zooming_value;
		if (win->zoom < 0.1)
			win->zoom = 0.1;
		if (win->zoom > 10)
			win->zoom = 10;
		win->off_x = x - img_x * win->zoom;
		win->off_y = y - img_y * win->zoom;
		mlx_destroy_image(win->mlx, win->image.img);
		initialize_img(win, WIDTH, HEIGHT);
		handle_output(win);
	}
	return (0);
}

void	initialize_img(t_win *win, int width, int height)
{
	win->image.img = mlx_new_image(win->mlx, width, height);
	win->image.addr = mlx_get_data_addr(win->image.img,
			&win->image.bits_per_pixel,
			&win->image.line_length,
			&win->image.endian);
	win->image.width = width;
	win->image.height = height;
}

int	handle_keypress(int key, void *x)
{
	t_win	*win;

	win = (t_win *)x;
	if (key == 65307 || key == 113)
	{
		mlx_destroy_image(win->mlx, win->image.img);
		mlx_destroy_window(win->mlx, win->window);
		mlx_destroy_display(win->mlx);
		free(win->mlx);
		free_map(*win->map);
		exit(0);
	}
	return (0);
}

int	handle_output(void *wind)
{
	t_win	*win;
	int		i;

	win = (t_win *)wind;
	i = 0;
	if (win->window != NULL && win->map)
	{
		if (win->map->map != NULL)
			put_map(win);
		mlx_put_image_to_window(win->mlx, win->window, win->image.img, 0, 0);
	}
	return (0);
}

int	cross(void *x)
{
	t_win	*win;

	win = (t_win *)x;
	mlx_destroy_image(win->mlx, win->image.img);
	mlx_destroy_window(win->mlx, win->window);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free_map(*win->map);
	exit(0);
	return (0);
}
