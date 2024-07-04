#include "parser.h"

int	main(int argc, char **argv)
{
	t_mini_rt	minirt;

	if (parser(argc, argv, &minirt))
		return (1);
	new_canvas(&minirt.canvas, WIDTH, HEIGHT, "Chapter 16");
	render(&minirt);
	mlx_image_to_window(minirt.canvas.mlx, minirt.canvas.img, 0, 0);
	mlx_close_hook(minirt.canvas.mlx, &quit, &minirt);
	mlx_key_hook(minirt.canvas.mlx, &handle_keyhook, &minirt);
	mlx_loop(minirt.canvas.mlx);
	free_world(&minirt.world);
	mlx_terminate(minirt.canvas.mlx);
	return (0);
}
