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

static void	handle_camera_position(t_mini_rt *rt, mlx_key_data_t *keydata)
{
	double		velocity;
	t_matrix	trans_m; 

	velocity = rt->canvas.mlx->delta_time * (rt->canvas.img->width * 0.05);
	if (keydata->key == MLX_KEY_RIGHT)
		translation(velocity, 0, 0, &trans_m);
	if (keydata->key == MLX_KEY_LEFT)
		translation(-velocity, 0, 0, &trans_m);
	if (keydata->key == MLX_KEY_UP)
	{
		if (keydata->modifier == MLX_SHIFT)
			translation(0, -velocity, 0, &trans_m);
		else
			translation(0, 0, velocity, &trans_m);
	}
	if (keydata->key == MLX_KEY_DOWN)
	{
		if (keydata->modifier == MLX_SHIFT)
			translation(0, velocity, 0, &trans_m);
		else
			translation(0, 0, -velocity, &trans_m);
	}
	multiply_matrices(&trans_m, &rt->camera.transform, &rt->camera.transform);
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
		&& (keydata.action == MLX_PRESS))
		handle_camera_position(rt, &keydata);
}

static void	handle_camera_rotation(t_mini_rt *rt, t_vector *delta)
{
	t_matrix		m[2];

	rotation_y(cos(delta->x), sin(delta->x), &m[0]);
	rotation_x(cos(-delta->y), sin(-delta->y), &m[1]);
	multiply_matrices(&m[0], &m[1], &m[0]);
	multiply_matrices(&m[0], &rt->camera.transform, &rt->camera.transform);
	set_transform_camera(&rt->camera, &rt->camera.transform);
	render(rt);
}

void	handle_mousehook(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param)
{
	t_mini_rt		*rt;
	t_vector		mouse_pos;
	static t_vector	last_mouse_pos;
	t_vector		delta;
	int32_t			xy[2];

	rt = (t_mini_rt *)param;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_set_cursor_mode(rt->canvas.mlx, MLX_MOUSE_HIDDEN);
		mlx_get_mouse_pos(rt->canvas.mlx, &xy[0], &xy[1]);
		new_vector((double)xy[0], (double)xy[1], 0, &last_mouse_pos);
	}
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
	{
		mlx_set_cursor_mode(rt->canvas.mlx, MLX_MOUSE_NORMAL);
		mlx_get_mouse_pos(rt->canvas.mlx, &xy[0], &xy[1]);
		new_vector((double)xy[0], (double)xy[1], 0, &mouse_pos);
		multiply(subtract(&mouse_pos, &last_mouse_pos, &delta), 0.002, &delta);
		if (delta.x != 0 || delta.y != 0)
			handle_camera_rotation(rt, &delta);
	}
}
