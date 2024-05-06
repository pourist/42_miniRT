#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"

#define WIDTH	1024
#define HEIGHT	1024
#define N_OBJS	7

void	create_background(t_world *world)
{
	t_shape		floor;
	t_shape		front_wall;
	t_shape		left_wall;
	t_shape		right_wall;
	t_color		a;
	t_color		b;
	t_matrix	multi;

	a = new_color(0.5, 0.5, 0.5);
	b = new_color(0.7, 0.7, 0.7);
	floor = new_plane();
	floor.material.specular = 0;
	floor.material.pattern = new_checkers_pattern(new_solid_pattern(a),
			new_solid_pattern(b));
	*floor.material.pattern.a = new_stripe_pattern(
			new_solid_pattern(new_color(0.9, 0.3, 0.3)),
			new_solid_pattern(new_color(0.6, 0.3, 0.3)));
	set_pattern_transform(floor.material.pattern.a, scaling(0.1, 0.1, 0.1));
	*floor.material.pattern.b = new_stripe_pattern(
			new_solid_pattern(a), new_solid_pattern(b));
	set_pattern_transform(floor.material.pattern.b, scaling(0.1, 0.1, 0.1));
	front_wall = new_plane();
	front_wall.material = floor.material;
	front_wall.material.pattern = new_blended_pattern(
			new_solid_pattern(a), new_solid_pattern(b));
	*front_wall.material.pattern.a = new_stripe_pattern(
			new_solid_pattern(new_color(0, 0.5, 0.1)),
			new_solid_pattern(new_color(0.8, 0.8, 0.8)));
	*front_wall.material.pattern.b = new_stripe_pattern(
			new_solid_pattern(new_color(0, 0.5, 0.1)),
			new_solid_pattern(new_color(0.8, 0.8, 0.8)));
	multi = transformations(2, rotation_x(cos(M_PI / 2), sin(M_PI / 2)),
			translation(0, 0, 5));
	set_transform(&front_wall, multi);
	set_pattern_transform(&front_wall.material.pattern, multi);
	set_pattern_transform(front_wall.material.pattern.a, rotation_z(cos(M_PI / 4), sin(M_PI / 4)));
	set_pattern_transform(front_wall.material.pattern.b, rotation_z(cos(-M_PI / 4), sin(-M_PI / 4)));
	right_wall = new_plane();
	right_wall.material = floor.material;
	right_wall.material.pattern = new_checkers_pattern(new_solid_pattern(a),
			new_solid_pattern(b));
	multi = transformations(3, rotation_x(cos(M_PI / 2), sin(M_PI / 2)),
			rotation_y(cos(M_PI / 3), sin(M_PI / 3)), translation(5, 0, 5));
	set_transform(&right_wall, multi);
	left_wall = new_plane();
	left_wall.material.pattern = new_checkers_pattern(new_solid_pattern(a),
			new_solid_pattern(b));
	multi = transformations(3, rotation_x(cos(M_PI / 2), sin(M_PI / 2)),
			rotation_y(cos(-M_PI / 3), sin(-M_PI / 3)), translation(-5, 0, 5));
	set_transform(&left_wall, multi);
	world->objs[0] = floor;
	world->objs[1] = front_wall;
	world->objs[2] = right_wall;
	world->objs[3] = left_wall;
}

void	create_spheres(t_world *world)
{
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_color		a;
	t_matrix	m;

	a = new_color(1, 1, 1);
	middle = new_sphere();
	middle.material.color = new_color(0.1, 1, 0.5);
	middle.material.pattern = new_checkers_pattern(new_solid_pattern(a),
			new_solid_pattern(middle.material.color));
	m = translation(-0.5, 1, 0.5);
	set_transform(&middle, m);
	m = scaling(0.4, 0.4, 0.4);
	set_pattern_transform(&middle.material.pattern, m);
	right = new_sphere();
	right.material.color = new_color(0.5, 1, 0.1);
	right.material.pattern = new_ring_pattern(new_solid_pattern(a),
			new_solid_pattern(right.material.color));
	m = multiply_matrices(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	set_transform(&right, m);
	set_pattern_transform(&right.material.pattern, m);
	left = new_sphere();
	left.material.color = new_color(1, 0.8, 0.1);
	left.material.pattern = new_full_gradient_pattern(new_solid_pattern(a),
			new_solid_pattern(left.material.color));
	m = multiply_matrices(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	set_transform(&left, m);
	set_pattern_transform(&left.material.pattern, m);
	world->objs[4] = middle;
	world->objs[5] = right;
	world->objs[6] = left;
}

void	create_ligts(t_world *world)
{
	world->lights = malloc(sizeof(t_light));
	world->lights_count = 1;
	world->lights[0] = new_light(new_point(-10, 10, -10), new_color(1, 1, 1));
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 2);
	from = new_point(0, 1, -5);
	to = new_point(0, 1, 0);
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
	free(world.objs[0].material.pattern.a);
	free(world.objs[0].material.pattern.b);
	free(world.objs[1].material.pattern.a);
	free(world.objs[1].material.pattern.b);
	free(world.objs[2].material.pattern.a);
	free(world.objs[2].material.pattern.b);
	free(world.objs[3].material.pattern.a);
	free(world.objs[3].material.pattern.b);
	free(world.objs[4].material.pattern.a);
	free(world.objs[4].material.pattern.b);
	free(world.objs[5].material.pattern.a);
	free(world.objs[5].material.pattern.b);
	free(world.objs[6].material.pattern.a);
	free(world.objs[6].material.pattern.b);
	free(world.objs);
	free(world.lights);
	mlx_terminate(canvas.mlx);
	return (0);
}
