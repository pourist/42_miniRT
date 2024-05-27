#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	600
#define HEIGHT	480
#define N_OBJS	1

t_shape	*create_dice(void)
{
	t_matrix	m;
	t_shape		*g;
	t_shape		*c;
	t_shape		*d1;
	t_shape		*csg;

	// s = malloc(1 * sizeof(t_shape));
	c = malloc(1 * sizeof(t_shape));
	g = malloc(6 * sizeof(t_shape));
	d1 = malloc(6 * sizeof(t_shape));
	csg = malloc(6 * sizeof(t_shape));
	new_cube(c);
	c->material.color = new_color(0.9, 0.2, 0.1);
	new_group(&g[0]);
	new_sphere(&d1[0]);
	d1[0].material.color = new_color(1, 1, 1);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[0], m);
	add_child(&g[0], &d1[0]);
	new_csg(DIFFERENCE, c, &g[0], &csg[0]);
	new_group(&g[1]);
	set_transform(&g[1], rotation_y(cos(M_PI / 2), sin(M_PI / 2)));
	new_sphere(&d1[1]);
	d1[1].material.color = new_color(1, 1, 1);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[1], m);
	add_child(&g[1], &d1[1]);
	new_csg(DIFFERENCE, &csg[0], &g[1], &csg[1]);
	new_group(&g[2]);
	set_transform(&g[2], rotation_y(cos(M_PI), sin(M_PI)));
	new_sphere(&d1[2]);
	d1[2].material.color = new_color(1, 1, 1);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[2], m);
	add_child(&g[2], &d1[2]);
	new_csg(DIFFERENCE, &csg[1], &g[2], &csg[2]);
	new_group(&g[3]);
	set_transform(&g[3], rotation_y(cos(-M_PI / 2), sin(-M_PI / 2)));
	new_sphere(&d1[3]);
	d1[3].material.color = new_color(1, 1, 1);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[3], m);
	add_child(&g[3], &d1[3]);
	new_csg(DIFFERENCE, &csg[2], &g[3], &csg[3]);
	new_group(&g[4]);
	set_transform(&g[4], rotation_y(cos(-M_PI / 2), sin(-M_PI / 2)));
	new_sphere(&d1[4]);
	d1[4].material.color = new_color(1, 1, 1);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[4], m);
	add_child(&g[4], &d1[4]);
	new_csg(DIFFERENCE, &csg[3], &g[4], &csg[4]);
	new_group(&g[5]);
	set_transform(&g[5], rotation_y(cos(M_PI / 2), sin(M_PI / 2)));
	new_sphere(&d1[5]);
	d1[5].material.color = new_color(1, 1, 1);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[5], m);
	add_child(&g[5], &d1[5]);
	new_csg(DIFFERENCE, &csg[4], &g[5], &csg[5]);
	return (&csg[5]);
}

void	create_scene(t_world *world)
{
	t_shape		*csg_dice1;
	t_matrix	m;

	// world->objs = malloc(1 * sizeof(t_shape));
	world->objs_count = 1;
	
	// t_shape	*s1;
	// s1 = malloc(1 * sizeof(t_shape));
	// new_glass_sphere(s1);
	// s1->material.diffuse = 0.1;
	// t_shape	*s2;
	// s2 = malloc(1 * sizeof(t_shape));
	// new_glass_sphere(s2);
	// s2->material.diffuse = 0.1;
	// set_transform(s1, translation(-0.65, 0, 0));
	// set_transform(s2, translation(0.65, 0, 0));
	// t_shape	*lens;
	// lens = world->objs;
	// new_csg(UNION, s1, s2, lens);

	world->objs = create_dice();
	csg_dice1 = world->objs;
	m = multiply_matrices(translation(0, 0, 0),
			rotation_x(cos(-M_PI_4), sin(-M_PI_4)));
	m = multiply_matrices(m, rotation_y(cos(-M_PI_4), sin(-M_PI_4)));
	set_transform(csg_dice1, m);
	world->objs = csg_dice1;
}

void	create_lights(t_world *world)
{
	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	world->lights[0] = new_light(new_point(-10, 10, -10), new_color(1, 1, 1));
	world->lights[1] = new_light(new_point(10, -10, -10), new_color(0.2, 0.5, 0.9));
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 3.0);
	from = new_point(0, 0, -8);
	to = new_point(0, 0, 10);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

int	main(void)
{
	t_world		world;
	t_camera	camera;
	t_canvas	canvas;

	world = new_world();
	create_lights(&world);
	create_camera(&camera);
	create_scene(&world);
	render(&canvas, &world, &camera);
	mlx_image_to_window(canvas.mlx, canvas.img, 0, 0);
	mlx_close_hook(canvas.mlx, &quit, &canvas);
	mlx_key_hook(canvas.mlx, &handle_keyhook, &canvas);
	mlx_loop(canvas.mlx);
	free_world(&world);
	mlx_terminate(canvas.mlx);
	return (0);
}
