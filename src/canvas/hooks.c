#include "canvas.h"

void	quit(void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
	mlx_delete_image(rt->canvas.mlx, rt->canvas.img);
	free_world(&rt->world);
	mlx_terminate(rt->canvas.mlx);
	exit(EXIT_SUCCESS);
}

void	handle_camera_position(t_mini_rt *rt, keys_t *key)
{
	double		velocity;
	t_matrix	translation_m;

	velocity = rt->canvas.mlx->delta_time * 1.0;
	if (*key == MLX_KEY_RIGHT)
		translation(velocity, 0, 0, &translation_m);
	if (*key == MLX_KEY_LEFT)
		translation(-velocity, 0, 0, &translation_m);
	if (*key == MLX_KEY_UP)
		translation(0, 0, velocity, &translation_m);
	if (*key == MLX_KEY_DOWN)
		translation(0, 0, -velocity, &translation_m);
	multiply_matrices(&translation_m, &rt->camera.transform,
		&rt->camera.transform);
	set_transform_camera(&rt->camera, &rt->camera.transform);
	render(rt);
}

void	handle_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
	if ((keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
		&& keydata.action == MLX_PRESS)
		quit(param);
	if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT
			|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		handle_camera_position(rt, &keydata.key);
}
