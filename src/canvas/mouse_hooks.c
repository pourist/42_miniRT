#include "canvas.h"

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

void	handle_scrollhook(double xdelta, double ydelta, void *param)
{
	t_mini_rt	*rt;

	(void)xdelta;
	rt = (t_mini_rt *)param;
	if (ydelta != 0 && rt->camera.focal_length + ydelta * 0.1 > 0.0)
	{
		rt->camera.focal_length += ydelta * 0.1;
		if (rt->camera.focal_length < 0.0)
			rt->camera.focal_length = 0.0;
	}
}
