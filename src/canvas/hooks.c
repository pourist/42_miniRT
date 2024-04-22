#include "canvas.h"

void	quit(void *param)
{
	t_canvas	*canvas;

	canvas = (t_canvas *)param;
	mlx_delete_image(canvas->mlx, canvas->img);
	mlx_terminate(canvas->mlx);
	exit(EXIT_SUCCESS);
}

void	handle_keyhook(mlx_key_data_t keydata, void *param)
{
	if ((keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
		&& keydata.action == MLX_PRESS)
		quit(param);
}
