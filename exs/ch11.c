#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"

#define WIDTH	512
#define HEIGHT	512
#define N_OBJS	6

void	create_background(t_world *world)
{
	t_shape		water;
	t_shape		water_bed;

	water = new_plane();
	water.material.color = new_color(0.0, 0.4, 0.8);
	water.material.diffuse = 0.3;
	water.material.reflective = 0.4;
	water.material.transparency = 0.9;
	water.material.refractive_index = WATER;
	water.cast_shadow = false;
	water_bed = new_plane();
	water_bed.material.color = new_color(0.5, 0.25, 0.1);
	set_transform(&water_bed, translation(0, -5, 0));
	water_bed.material.diffuse = 0.9;
	water_bed.material.reflective = 0.0;
	water_bed.material.transparency = 0.0;
	water_bed.material.specular = 0.0;
	water_bed.material.refractive_index = AIR;
	world->objs[0] = water;
	world->objs[1] = water_bed;
}

void	create_spheres(t_world *world)
{
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_shape		behind;
	t_matrix	m;

	middle = new_sphere();
	middle.material.color = new_color(0.9, 0.9, 0.9);
	m = translation(-0.5, 0, 0.5);
	set_transform(&middle, m);
	middle.material.ambient = new_color(0.1, 0.1, 0.1);
	middle.material.diffuse = 0.1;
	middle.material.specular = 5.0;
	middle.material.shininess = 1200.0;
	middle.material.reflective = 0.9;
	middle.material.transparency = 0.9;
	middle.material.refractive_index = GLASS;
	right = new_sphere();
	right.material.color = new_color(5, 0.5, 0.1);
	m = multiply_matrices(translation(2, -0.5, 0), scaling(0.2, 0.2, 0.2));
	set_transform(&right, m);
	left = new_sphere();
	left.material.reflective = 0.9;
	left.material.color = new_color(0, 0, 0);
	left.material.pattern = new_full_gradient_pattern(new_solid_pattern(new_color(1, 0, 0)),
			new_solid_pattern(left.material.color));
	m = multiply_matrices(translation(-2, -0.2, -1), scaling(0.33, 0.33, 0.33));
	set_transform(&left, m);
	behind = new_sphere();
	behind.material.color = new_color(0.8, 0, 0);
	m = multiply_matrices(translation(-0.2, 0.2, -0.2), scaling(0.33, 0.33, 0.33));
	set_transform(&behind, m);
	world->objs[2] = middle;
	world->objs[3] = right;
	world->objs[4] = left;
	world->objs[5] = behind;
}

void	create_ligts(t_world *world)
{
	world->lights = malloc(sizeof(t_light));
	world->lights_count = 1;
	world->lights[0] = new_light(new_point(-5, 5, -5), new_color(1, 1, 1));
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 3);
	from = new_point(0, 1, -8);
	to = new_point(0, 0, 0);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

int	main(void)
{
	t_world		world;
	t_camera	camera;
	t_canvas	canvas;

	world = new_world();
	world.objs = malloc(sizeof(t_shape) * N_OBJS);
	world.objs_count = N_OBJS;
	create_background(&world);
	create_spheres(&world);
	create_ligts(&world);
	create_camera(&camera);
	render(&canvas, &world, &camera);
	mlx_image_to_window(canvas.mlx, canvas.img, 0, 0);
	mlx_close_hook(canvas.mlx, &quit, &canvas);
	mlx_key_hook(canvas.mlx, &handle_keyhook, &canvas);
	mlx_loop(canvas.mlx);
	free(world.objs);
	free(world.lights);
	mlx_terminate(canvas.mlx);
	return (0);
}
