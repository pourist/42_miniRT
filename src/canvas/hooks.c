#include "canvas.h"

void	quit(void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
	free_world(&rt->world);
	mlx_delete_image(rt->canvas.mlx, rt->canvas.img);
	mlx_terminate(rt->canvas.mlx);
	exit(EXIT_SUCCESS);
}

static void	set_camera_position(t_mini_rt *rt, mlx_key_data_t *keydata)
{
	double		velocity;
	t_matrix	trans_m; 

	velocity = rt->canvas.mlx->delta_time * (rt->canvas.img->width * 0.05);
	if (keydata->key == MLX_KEY_RIGHT || keydata->key == MLX_KEY_D)
		translation(velocity, 0, 0, &trans_m);
	if (keydata->key == MLX_KEY_LEFT || keydata->key == MLX_KEY_A)
		translation(-velocity, 0, 0, &trans_m);
	if (keydata->key == MLX_KEY_UP || keydata->key == MLX_KEY_W)
		translation(0, 0, velocity, &trans_m);
	if (keydata->key == MLX_KEY_DOWN || keydata->key == MLX_KEY_S)
		translation(0, 0, -velocity, &trans_m);
	multiply_matrices(&trans_m, &rt->camera.transform, &rt->camera.transform);
}

static void	set_camera_position_shift(t_mini_rt *rt, mlx_key_data_t *keydata)
{
	double		translation_velocity;
	double		rotation_velocity;
	t_matrix	trans_m; 

	translation_velocity = rt->canvas.mlx->delta_time
		* (rt->canvas.img->width * 0.05);
	rotation_velocity = rt->canvas.mlx->delta_time
		* (rt->canvas.img->width * 0.002);
	if (keydata->key == MLX_KEY_RIGHT || keydata->key == MLX_KEY_D)
		rotation_z(cos(-rotation_velocity), sin(-rotation_velocity),
			&trans_m);
	if (keydata->key == MLX_KEY_LEFT || keydata->key == MLX_KEY_A)
		rotation_z(cos(rotation_velocity), sin(rotation_velocity),
			&trans_m);
	if (keydata->key == MLX_KEY_UP || keydata->key == MLX_KEY_W)
		translation(0, -translation_velocity, 0, &trans_m);
	if (keydata->key == MLX_KEY_DOWN || keydata->key == MLX_KEY_S)
		translation(0, translation_velocity, 0, &trans_m);
	multiply_matrices(&trans_m, &rt->camera.transform, &rt->camera.transform);
}

inline bool	is_move_key(keys_t *key)
{
	return (*key == MLX_KEY_RIGHT || *key == MLX_KEY_D || *key == MLX_KEY_LEFT
		|| *key == MLX_KEY_A || *key == MLX_KEY_UP || *key == MLX_KEY_W
		|| *key == MLX_KEY_DOWN || *key == MLX_KEY_S);
}

void	handle_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
	if ((keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
		&& keydata.action == MLX_PRESS)
		quit(param);
	if (is_move_key(&keydata.key) && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT) && keydata.modifier == 0)
		set_camera_position(rt, &keydata);
	if (is_move_key(&keydata.key) && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT) && keydata.modifier == MLX_SHIFT)
		set_camera_position_shift(rt, &keydata);
	if (is_move_key(&keydata.key) && keydata.action == MLX_RELEASE)
	{
		set_transform_camera(&rt->camera, &rt->camera.transform);
		render(rt);
	}
	if ((keydata.key == MLX_KEY_R || keydata.key == MLX_KEY_SPACE)
		&& keydata.action == MLX_PRESS)
		render(rt);
}
