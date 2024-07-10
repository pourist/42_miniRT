#include "parser.h"

int	main(int argc, char **argv)
{
	t_mini_rt	minirt;

	if (parser(argc, argv, &minirt))
		return (1);
	new_canvas(&minirt.canvas, WIDTH, HEIGHT, "MiniRT");
	create_bvh(&minirt.world);
	render(&minirt);
	printf("Render time: %f's\n", mlx_get_time());
	mlx_image_to_window(minirt.canvas.mlx, minirt.canvas.img, 0, 0);
	mlx_close_hook(minirt.canvas.mlx, &quit, &minirt);
	mlx_key_hook(minirt.canvas.mlx, &handle_keyhook, &minirt);
	//mlx_cursor_hook(minirt.canvas.mlx, &handle_cursorhook, &minirt);
	mlx_loop(minirt.canvas.mlx);
	mlx_set_mouse_pos(minirt.canvas.mlx, minirt.canvas.mlx->width * 0.5,
		minirt.canvas.mlx->height * 0.5);
	free_world(&minirt.world);
	mlx_terminate(minirt.canvas.mlx);
	return (0);
}
