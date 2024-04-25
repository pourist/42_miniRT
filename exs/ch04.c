
#include "tuples.h"
#include "canvas.h"
#include "matrices.h"
#include "utils.h"
#include <stdio.h>

static void	write_circle(mlx_image_t *img, int xy[2], int radius, t_color color)
{
	int	x_beg_end[2];
	int	y_beg_end[2];
	int	square_r;
	int	distance;

	x_beg_end[0] = xy[0] - radius;
	x_beg_end[1] = xy[0] + radius;
	y_beg_end[1] = xy[1] + radius;
	while (x_beg_end[0] < x_beg_end[1])
	{
		y_beg_end[0] = xy[1] - radius;
		while (y_beg_end[0] < y_beg_end[1])
		{
			square_r = radius * radius;
			distance = (x_beg_end[0] - xy[0]) * (x_beg_end[0] - xy[0])
				+ (y_beg_end[0] - xy[1]) * (y_beg_end[0] - xy[1]);
			if (distance <= square_r)
				write_pixel(img, x_beg_end[0], y_beg_end[0], color);
			y_beg_end[0]++;
		}
		x_beg_end[0]++;
	}
}

static void	render_clock(t_canvas *canvas)
{
	t_color		color;
	t_matrix	transformations[2];
	int			i;
	double		radius;
	t_point		points[2];

	color = new_color(0.5, 1, 0.5, 1);
	transformations[0] = translation(
			*canvas->width * 0.5, 0, *canvas->height * 0.5);
	if (*canvas->width < *canvas->height)
		radius = *canvas->width * 3 / 8;
	else
		radius = *canvas->height * 3 / 8;
	points[0] = new_point(0, 0, radius);
	i = -1;
	while (++i < 12)
	{
		transformations[1] = rotation_y(i * M_PI / 6);
		points[1] = multiply_matrix_by_tuple(
				multiply_matrices(transformations[0], transformations[1]),
				points[0]);
		write_circle(canvas->img, (int [2]){points[1].x, points[1].z},
			5, color);
	}
}

int	main(void)
{
	t_canvas	rt;

	if (!new_canvas(&rt, 900, 550, "Chapter 04"))
		return (1);
	render_clock(&rt);
	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	mlx_close_hook(rt.mlx, &quit, &rt);
	mlx_key_hook(rt.mlx, &handle_keyhook, &rt);
	mlx_loop(rt.mlx);
	mlx_terminate(rt.mlx);
	return (0);
}
