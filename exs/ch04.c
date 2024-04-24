
#include "tuples.h"
#include "canvas.h"
#include "matrices.h"
#include "utils.h"
#include <stdio.h>

static void	write_dot(mlx_image_t *img, int x, int y, t_color color)
{
	write_pixel(img, x, y, color);
	write_pixel(img, x + 1, y, color);
	write_pixel(img, x, y + 1, color);
	write_pixel(img, x - 1, y, color);
	write_pixel(img, x, y - 1, color);
}

static void	render_clock(t_canvas *canvas)
{
	t_color	c;
	t_point	p;
	t_point	center;
	double	clock_rad;
	t_matrix	r;
	int			i;

	clock_rad = 500 * 3 / 8;
	c = new_color(1, 1, 1, 1);
	p = new_point(0, 0, 1);
	center = new_point(0, 0, 0);
	r = rotation_y(3 * (M_PI / 6));
	i = 0;
	write_dot(canvas->img, canvas->)
	while (i < 11)
	{

	}
}

int	main(void)
{
	t_canvas	rt;

	if (!new_canvas(&rt, 900, 550, "Chapter 04"))
		return (1);
	render_projectile_motion(&rt);
	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	mlx_close_hook(rt.mlx, &quit, &rt);
	mlx_key_hook(rt.mlx, &handle_keyhook, &rt);
	mlx_loop(rt.mlx);
	mlx_terminate(rt.mlx);
	return (0);
}
