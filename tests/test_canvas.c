#include "test.h"

Test(canvas, create_a_canvas)
{
	t_canvas	canvas;

	new_canvas(&canvas, 10, 20, "Test");
	cr_assert(eq(u32, canvas.mlx->width, 10));
	cr_assert(eq(u32, canvas.mlx->height, 20));
	mlx_delete_image(canvas.mlx, canvas.img);
	mlx_terminate(canvas.mlx);
}

Test(canvas, write_a_pixel)
{
	t_canvas	canvas;
	t_color		c;

	new_canvas(&canvas, 10, 20, "Test");
	write_pixel(canvas.img, 2, 3, color(1, 0, 0, 1));
	c = read_pixel(canvas.img, 2, 3);
	cr_assert(epsilon_eq(dbl, c.r, 1, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, 0, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, 0, DBL_EPSILON));
	mlx_delete_image(canvas.mlx, canvas.img);
	mlx_terminate(canvas.mlx);
}
