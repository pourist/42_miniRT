#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include <stdio.h>

#define WIDTH	512
#define HEIGHT	512

typedef struct s_params {
	double		world_x;
	double		world_y;
	double		world_z;
	double		wall_size;
	double		pixel_size;
	double		half;
	t_point		ray_origin;
	t_shape		sphere;
	uint32_t	sphere_color;
	uint32_t	bg_color;
}	t_params;

void	render_sphere(t_canvas *rt, t_params *params, t_light *light)
{
	int				xy[2];
	t_hit			*xs;
	t_point			pos;
	t_ray			ray;
	t_eye_normal	view;
	t_hit			*hits;

	xy[1] = -1;
	while (++xy[1] < HEIGHT)
	{
		params->world_y = params->half - params->pixel_size * xy[1];
		xy[0] = -1;
		while (++xy[0] < WIDTH)
		{
			xs = NULL;
			params->world_x = -params->half + params->pixel_size * xy[0];
			pos = new_point(params->world_x, params->world_y,
					params->world_z);
			ray = new_ray(params->ray_origin,
					normalize(subtract(pos, params->ray_origin)));
			intersect(&xs, &params->sphere, ray);
			hits = hit(xs);
			if (hits)
			{
				pos = position(ray, hits->t);
				view.normal_v = normal_at(&params->sphere, pos);
				view.eye_v = negate(ray.direction);
				params->sphere_color = get_rgba(
						lighting(&params->sphere.material, light, &pos, &view));
				write_pixel(rt->img, xy[0], xy[1], params->sphere_color);
			}
			else
				write_pixel(rt->img, xy[0], xy[1], params->bg_color);
		}
	}
}

void	set_params(t_params *params)
{
	params->world_x = 0;
	params->world_y = 0;
	params->world_z = 10;
	params->wall_size = 7;
	params->pixel_size = params->wall_size / HEIGHT;
	params->half = params->wall_size * 0.5;
	params->ray_origin = new_point(0, 0, -5);
	params->sphere_color = get_rgba(new_color(0.6, 0.1, 0.1, 1));
	params->bg_color = get_rgba(new_color(0.0, 0.0, 0.0, 1));
	params->sphere = new_sphere();
	params->sphere.material.color.g = 0.2;
	// set_transform(&params->sphere, scaling(1, 0.5, 1));
	// set_transform(&params->sphere, scaling(0.5, 1, 1));
	// set_transform(&params->sphere, multiply_matrices(
	// 		rotation_z(cos(M_PI / 4), sin(M_PI / 4)), scaling(0.5, 1, 1)));
	// set_transform(&params->sphere, transformations(2,
	// 		scaling(0.5, 1, 1), rotation_z(cos(M_PI_4), sin(M_PI_4))));
	// set_transform(&params->sphere, multiply_matrices(
	// 		shearing((t_shearing){1, 0}, (t_shearing){0}, (t_shearing){0}),
	// 		scaling(0.5, 1, 1)));
	// set_transform(&params->sphere, transformations(2, scaling(0.5, 1, 1),
	// 			shearing((t_shearing){1, 0}, (t_shearing){0, 0}, (t_shearing){0, 0})));
}

int	main(void)
{
	t_canvas	rt;
	t_params	params;
	t_light		light;

	if (!new_canvas(&rt, WIDTH, HEIGHT, "Chapter 05"))
		return (1);
	set_params(&params);
	light = new_light(new_point(-10, 10, -10), new_color(1, 1, 1, 1));
	render_sphere(&rt, &params, &light);
	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	mlx_close_hook(rt.mlx, &quit, &rt);
	mlx_key_hook(rt.mlx, &handle_keyhook, &rt);
	mlx_loop(rt.mlx);
	mlx_terminate(rt.mlx);
	return (0);
}
