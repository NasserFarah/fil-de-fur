/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnasser <fnasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:14:15 by fnasser           #+#    #+#             */
/*   Updated: 2025/11/09 21:02:21 by fnasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/X.h>
# include <math.h>
# include "/home/fnasser/local/include/mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "gnl/get_next_line.h"

# define HEIGHT		1080
# define WIDTH		1920

typedef struct s_point
{
	ssize_t	x;
	ssize_t	y;
	int		color;
}			t_point;

typedef struct s_line
{
	int	delta_x;
	int	delta_y;
	int	direction_x;
	int	direction_y;
	int	error;
}				t_line;

typedef struct s_map
{
	ssize_t	**map;
	ssize_t	**color;
	ssize_t	row;
	ssize_t	col;
	ssize_t	min_z;
	ssize_t	max_z;
}	t_map;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_win
{
	void	*mlx;
	void	*window;
	t_image	image;
	t_map	*map;
	float	off_x;
	float	off_y;
	float	zoom;
}	t_win;

typedef struct s_wireframe
{
	int		scale;
	int		off_x;
	int		off_y;
	float	zoom;
	ssize_t	x;
	ssize_t	y;
	t_point	curr;
	t_point	next;
	t_point	down;
}	t_wireframe;

typedef struct s_center
{
	int	max_x;
	int	max_y;
	int	min_x;
	int	min_y;
}	t_center;

typedef struct s_parse
{
	char		*line;
	ssize_t		i;
	int			dim;
}	t_parse;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	float	t;
}	t_color;

ssize_t	get_map_rows(t_map *map, char *file);
t_map	parse_map(int fd, t_map *map, char *file);
t_map	*parse_line(char *line, int col, t_map *map, ssize_t index);
t_point	project(t_wireframe *w, ssize_t **map);
void	img_pix_put(t_image *img, int x, int y, int color);
void	matrix(t_parse *p, int fd, t_map *map);
void	alloc_map(t_map *map);
void	center(t_map *map, int scale, int *off_x, int *off_y);
void	center_top_left(t_point *p, t_center *dim, int scale);
void	center_top_right(t_point *p, t_map *map, t_center *dim, int scale);
void	center_bottom_left(t_point *p, t_center *dim, int scale, t_map *map);
void	center_bottom_right(t_point *p, t_center *dim, int scale, t_map *map);
void	put_line_same_color(t_image *img, t_point *f, t_point l, t_line *line);
void	put_line_diff_color(t_image *img, t_point f, t_point l, t_line *line);
void	draw_lines(t_win *win, t_wireframe *wire);
void	draw_next(t_wireframe *wire, t_win *win);
void	draw_down(t_wireframe *wire, t_win *win);
void	free_map(t_map map);
void	put_map(t_win *win);
void	initialize_img(t_win *win, int width, int height);
void	init_direction(t_line *line, t_point f, t_point l);
void	put_line(t_image *img, t_point f, t_point l);
void	ft_free_split(char **splited);
void	get_min_max_z(t_map *map);
void	init_fdf(t_map *map);
int		zoom(int button, int x, int y, t_win *win);
int		ft_color_matrix(char *splited);
int		handle_keypress(int key, void *x);
int		handle_output(void *wind);
int		ft_count_lines(int fd);
int		scale(t_map *map);
int		cross(void *x);
int		check_fdf_file(char *c);

#endif
