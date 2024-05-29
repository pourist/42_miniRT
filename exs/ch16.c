#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	600
#define HEIGHT	480
#define N_OBJS	1

t_shape	*create_dice(t_color color)
{
	t_matrix	m;
	t_shape		*g;
	t_shape		*c;
	t_shape		*s;
	t_shape		*d1;
	t_shape		*d2;
	t_shape		*d3;
	t_shape		*d4;
	t_shape		*d5;
	t_shape		*d6;
	t_shape		*csg;

	s = malloc(1 * sizeof(t_shape));
	c = malloc(1 * sizeof(t_shape));
	g = malloc(6 * sizeof(t_shape));
	d1 = malloc(6 * sizeof(t_shape));
	d2 = malloc(5 * sizeof(t_shape));
	d3 = malloc(4 * sizeof(t_shape));
	d4 = malloc(3 * sizeof(t_shape));
	d5 = malloc(2 * sizeof(t_shape));
	d6 = malloc(1 * sizeof(t_shape));
	csg = malloc(7 * sizeof(t_shape));
	new_cube(c);
	new_sphere(s);
	c->material.color = color;
	c->material.shininess = 1300;
	c->material.diffuse = 1.0;
	c->material.specular = 1.0;
	s->material.color = color;
	s->material.shininess = 1300;
	s->material.diffuse = 1.0;
	s->material.specular = 1.0;
	set_transform(s, scaling(1.4, 1.4, 1.4));
	new_csg(INTERSECT, s, c, &csg[0]);
	new_group(&g[0]);
	new_sphere(&d1[0]);
	d1[0].material.color = new_color(1, 1, 1);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[0], m);
	add_child(&g[0], &d1[0]);
	new_csg(DIFFERENCE, &csg[0], &g[0], &csg[1]);
	new_sphere(&d1[1]);
	d1[1].material.color = new_color(1, 1, 1);
	d2[0] = d1[1];
	m = multiply_matrices(translation(-0.5, 0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[1], m);
	m = multiply_matrices(translation(0.5, -0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d2[0], m);
	new_group(&g[1]);
	set_transform(&g[1], rotation_y(cos(M_PI_2), sin(M_PI_2)));
	add_child(&g[1], &d1[1]);
	add_child(&g[1], &d2[0]);
	new_csg(DIFFERENCE, &csg[1], &g[1], &csg[2]);
	new_sphere(&d1[2]);
	d1[2].material.color = new_color(1, 1, 1);
	d2[1] = d1[2];
	d3[0] = d1[2];
	m = multiply_matrices(translation(-0.5, 0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[2], m);
	m = multiply_matrices(translation(0.5, -0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d2[1], m);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d3[0], m);
	new_group(&g[2]);
	set_transform(&g[2], rotation_y(cos(M_PI), sin(M_PI)));
	add_child(&g[2], &d1[2]);
	add_child(&g[2], &d2[1]);
	add_child(&g[2], &d3[0]);
	new_csg(DIFFERENCE, &csg[2], &g[2], &csg[3]);
	new_sphere(&d1[3]);
	d1[3].material.color = new_color(1, 1, 1);
	d2[2] = d1[3];
	d3[1] = d1[3];
	d4[0] = d1[3];
	m = multiply_matrices(translation(-0.5, 0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[3], m);
	m = multiply_matrices(translation(0.5, -0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d2[2], m);
	m = multiply_matrices(translation(-0.5, -0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d3[1], m);
	m = multiply_matrices(translation(0.5, 0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d4[0], m);
	new_group(&g[3]);
	set_transform(&g[3], rotation_y(cos(-M_PI_2), sin(-M_PI_2)));
	add_child(&g[3], &d1[3]);
	add_child(&g[3], &d2[2]);
	add_child(&g[3], &d3[1]);
	add_child(&g[3], &d4[0]);
	new_csg(DIFFERENCE, &csg[3], &g[3], &csg[4]);
	new_sphere(&d1[4]);
	d1[4].material.color = new_color(1, 1, 1);
	d2[3] = d1[4];
	d3[2] = d1[4];
	d4[1] = d1[4];
	d5[0] = d1[4];
	m = multiply_matrices(translation(-0.5, 0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[4], m);
	m = multiply_matrices(translation(0.5, -0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d2[3], m);
	m = multiply_matrices(translation(-0.5, -0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d3[2], m);
	m = multiply_matrices(translation(0.5, 0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d4[1], m);
	m = multiply_matrices(translation(0, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d5[0], m);
	new_group(&g[4]);
	set_transform(&g[4], rotation_x(cos(-M_PI_2), sin(-M_PI_2)));
	add_child(&g[4], &d1[4]);
	add_child(&g[4], &d2[3]);
	add_child(&g[4], &d3[2]);
	add_child(&g[4], &d4[1]);
	add_child(&g[4], &d5[0]);
	new_csg(DIFFERENCE, &csg[4], &g[4], &csg[5]);
	new_sphere(&d1[5]);
	d1[5].material.color = new_color(1, 1, 1);
	d2[4] = d1[5];
	d3[3] = d1[5];
	d4[2] = d1[5];
	d5[1] = d1[5];
	d6[0] = d1[5];
	m = multiply_matrices(translation(-0.5, 0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d1[5], m);
	m = multiply_matrices(translation(0.5, -0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d2[4], m);
	m = multiply_matrices(translation(-0.5, -0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d3[3], m);
	m = multiply_matrices(translation(0.5, 0.5, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d4[2], m);
	m = multiply_matrices(translation(-0.5, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d5[1], m);
	m = multiply_matrices(translation(0.5, 0, -1), scaling(0.2, 0.2, 0.2));
	set_transform(&d6[0], m);
	new_group(&g[5]);
	set_transform(&g[5], rotation_x(cos(M_PI_2), sin(M_PI_2)));
	add_child(&g[5], &d1[5]);
	add_child(&g[5], &d2[4]);
	add_child(&g[5], &d3[3]);
	add_child(&g[5], &d4[2]);
	add_child(&g[5], &d5[1]);
	add_child(&g[5], &d6[0]);
	new_csg(DIFFERENCE, &csg[5], &g[5], &csg[6]);
	return (&csg[6]);
}

void	create_scene(t_world *world)
{
	t_shape		*csg_dice1;
	t_shape		*csg_dice2;
	t_shape		*csg_dice3;
	t_shape		*floor;
	t_shape		*left_wall;
	t_shape		*right_wall;
	t_matrix	m;

	world->objs = malloc(2 * sizeof(t_shape));
	world->objs_count = 2;
	
	csg_dice1 = create_dice(new_color(0.6, 0.2, 0.2));
	m = multiply_matrices(translation(1.4, 0, 0.4),
			rotation_x(cos(-M_PI), sin(-M_PI)));
	m = multiply_matrices(m, rotation_y(cos(-M_PI_4), sin(-M_PI_4)));
	set_transform(csg_dice1, m);
	csg_dice2 = create_dice(new_color(0.2, 0.2, 0.6));
	m = multiply_matrices(translation(-1.4, 0, -0.4),
			rotation_x(cos(M_PI), sin(M_PI)));
	m = multiply_matrices(m, rotation_y(cos(M_PI_4), sin(M_PI_4)));
	set_transform(csg_dice2, m);
	csg_dice3 = create_dice(new_color(0.2, 0.6, 0.2));
	m = multiply_matrices(translation(0, 2, 0),
			rotation_x(cos(M_PI), sin(M_PI)));
	m = multiply_matrices(m, rotation_y(cos(M_PI_2), sin(M_PI_2)));
	set_transform(csg_dice3, m);
	floor = malloc(1 * sizeof(t_shape));
	new_plane(floor);
	floor->material.reflective = 0.3;
	floor->material.color = new_color(1, 1, 1);
	floor->material.pattern = new_checkers_pattern(new_solid_pattern(new_color(0.7, 0.7, 0.7)),
			new_solid_pattern(new_color(0.9, 0.9, 0.9)));
	set_transform(floor, translation(0, -1, 0));
	left_wall = malloc(1 * sizeof(t_shape));
	right_wall = malloc(1 * sizeof(t_shape));
	new_plane(left_wall);
	new_plane(right_wall);
	left_wall->material.color = new_color(1, 1, 1);
	left_wall->material.reflective = 0.3;
	left_wall->material.pattern = new_checkers_pattern(new_solid_pattern(new_color(0.7, 0.7, 0.7)),
			new_solid_pattern(new_color(0.9, 0.9, 0.9)));
	right_wall->material.color = new_color(1, 1, 1);
	right_wall->material.reflective = 0.3;
	right_wall->material.pattern = new_checkers_pattern(new_solid_pattern(new_color(0.7, 0.7, 0.7)),
			new_solid_pattern(new_color(0.9, 0.9, 0.9)));
	m = multiply_matrices(translation(15, 0, 0),
			rotation_y(cos(M_PI_4), sin(M_PI_4)));
	m = multiply_matrices(m, rotation_x(cos(M_PI_2), sin(M_PI_2)));
	set_transform(left_wall, m);
	m = multiply_matrices(translation(-15, 0, 0),
			rotation_y(cos(-M_PI_4), sin(-M_PI_4)));
	m = multiply_matrices(m, rotation_x(cos(M_PI_2), sin(M_PI_2)));
	set_transform(right_wall, m);
	new_group(&world->objs[0]);
	new_group(&world->objs[1]);
	add_child(&world->objs[0], csg_dice1);
	add_child(&world->objs[0], csg_dice2);
	add_child(&world->objs[0], csg_dice3);
	add_child(&world->objs[1], floor);
	add_child(&world->objs[1], left_wall);
	add_child(&world->objs[1], right_wall);
}

void	create_lights(t_world *world)
{
	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	world->lights[0] = new_light(new_point(-10, 10, -10), new_color(0.9, 0.9, 0.9));
	world->lights[1] = new_light(new_point(5, -5, -10), new_color(0.1, 0.1, 0.1));
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 3.0);
	from = new_point(0, 6, -10);
	to = new_point(0, -2, 10);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

int	main(void)
{
	t_mini_rt	rt;

	rt.world = new_world();
	create_lights(&rt.world);
	create_camera(&rt.camera);
	create_scene(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 16");
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free_world(&rt.world);
	mlx_terminate(rt.canvas.mlx);
}
