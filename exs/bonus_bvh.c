#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	800
#define HEIGHT	600
#define N_OBJS	1

void	create_raw_bbox(t_shape *bbox)
{
	t_matrix	m[2];

	new_cube(bbox);
	bbox->cast_shadow = false;
	multiply_matrices(translation(-3.9863, -0.1217, -1.1820, &m[0]),
		scaling(3.73335, 2.5845, 1.6283, &m[1]), &m[0]);
	multiply_matrices(&m[0], translation(1, 0, 0, &m[1]), &m[0]);
	set_transform(bbox, &m[0]);
}

void	create_bbox(t_shape *bbox)
{
	t_matrix	m[2];

	new_cube(bbox);
	multiply_matrices(scaling(0.268, 0.268, 0.268, &m[0]),
		translation(0, 0.1217, 0, &m[1]), &m[0]);
	set_transform(bbox, &m[0]);
}

void	create_pedestal(t_shape *pedestal)
{
	t_matrix	m[2];

	new_cylinder(pedestal);
	pedestal->cyl.min = -0.15;
	pedestal->cyl.max = 0;
	pedestal->cyl.closed = true;
	pedestal->material.color = new_color(0.2, 0.2, 0.2);
	pedestal->material.ambien = new_color(0, 0, 0);
	pedestal->material.diffuse = 0.8;
	pedestal->material.specular = 0;
	pedestal->material.reflective = 0.2;
}

void	create_dragon(t_shape *dragon)
{
	t_obj_loader	loader;
	t_matrix		m[2];

	new_obj_loader(&loader);
	parse_obj_file(&loader, "../obj_files/dragon.obj");
	*dragon = loader.default_group;
	multiply_matrices(scaling(0.268, 0.268, 0.268, &m[0]),
		translation(0, 0.1217, 0, &m[1]), &m);
	set_transform(dragon, &m[0]);
}

void	create_scene(t_world *world)
{
	t_shape			*tmp;
	t_matrix		m[2];
	int				obj_i;
	int				obj_in_i;

	world->objs = malloc(6 * sizeof(t_shape));
	world->objs_count = 6;
	world->objs_inside = malloc(22 * sizeof(t_shape));
	world->objs_inside_count = 22;
	obj_i = 0;
	obj_in_i = 0;
	new_group(&world->objs[obj_i]);
	tmp = &world->objs[obj_i];
	set_transform(tmp, translation(0, 2, 0, &m[0]));
	obj_i++;
	create_pedestal(&world->objs_inside[obj_in_i]);
	add_child(tmp, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	new_group(&world->objs_inside[obj_in_i]);
}

void	create_lights(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(4 * sizeof(t_light));
	world->lights_count = 4;
	new_point(-10, 100, -100, &p);
	c = new_color(1, 1, 1);
	new_light(&p, &c, &world->lights[0]);
	new_point(0, 100, 0, &p);
	c = new_color(0.1, 0.1, 0.1);
	new_light(&p, &c, &world->lights[1]);
	new_point(100, 10, -25, &p);
	c = new_color(0.2, 0.2, 0.2);
	new_light(&p, &c, &world->lights[2]);
	new_point(-100, 10, -25, &p);
	c = new_color(0.2, 0.2, 0.2);
	new_light(&p, &c, &world->lights[3]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;
	t_matrix	m;

	new_camera(camera, WIDTH, HEIGHT, 1.2);
	new_point(0, 2.5, -10, &from);
	new_point(0, 1, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&m));
}

int	main(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	create_lights(&rt.world);
	create_camera(&rt.camera);
	create_scene(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Bonus BVH");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free_world(&rt.world);
	mlx_terminate(rt.canvas.mlx);
	return (0);
}
