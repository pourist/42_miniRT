/* #include "parser.h"

int	main(int argc, char **argv)
{
	t_mini_rt	minirt;
	// t_shape	*s;

	if (parser(argc, argv, &minirt))
		return (1);
	// printf("camera 	pos:       h: %f v: %f fov: %f \n",minirt.camera.hsize, minirt.camera.vsize,  minirt.camera.fov);
    // printf("----- Sphere :     r: %f g: %f b: %f \n", minirt.world.objs[0].material.color.r,minirt.world.objs[0].material.color.g , minirt.world.objs[0].material.color.b);
	// printf("Ambient:           r: %f g: %f b: %f \n", minirt.world.ambient.r, minirt.world.ambient.g, minirt.world.ambient.b);
	// printf("Light rgb:         r: %f g: %f b: %f \n", minirt.world.lights[0].intensity.r, minirt.world.lights[0].intensity.g, minirt.world.lights[0].intensity.b);
	// printf("Light pos:         x: %f y: %f z: %f \n", minirt.world.lights[0].position.x, minirt.world.lights[0].position.y, minirt.world.lights[0].position.z);
	// printf("Sphere :           x: %f y: %f z: %f \n", minirt.world.objs[0].sphere.origin.x, minirt.world.objs[0].sphere.origin.y , minirt.world.objs[0].sphere.origin.z);
	// (void)argc;
	// (void)argv;
	new_canvas(&minirt.canvas, WIDTH, HEIGHT, "Chapter 16");
	// minirt.world = new_world();
	// minirt.world.objs = malloc(sizeof(t_shape));
	// minirt.world.objs_count = 1;
	// s = &minirt.world.objs[0];
	// new_sphere(s);
	t_point from;
    t_point to;
    t_vector up;
	new_camera(&minirt.camera ,WIDTH, HEIGHT, M_PI_2);
	new_point(0, 10, -10, &from);
	new_point(0, 9, -10, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(&minirt.camera, view_transform(&from, &to, &up, &minirt.camera.transform));
	// minirt.world.lights = malloc(1 * sizeof(t_light));
	// minirt.world.lights_count = 1;
	// minirt.world.lights[0] = new_light(new_point(-10, 10, -10), new_color(0.9, 0.9, 0.9));
	render(&minirt);
	mlx_image_to_window(minirt.canvas.mlx, minirt.canvas.img, 0, 0);
	mlx_close_hook(minirt.canvas.mlx, &quit, &minirt.canvas);
	mlx_key_hook(minirt.canvas.mlx, &handle_keyhook, &minirt.canvas);
	mlx_loop(minirt.canvas.mlx);
	free_world(&minirt.world);
	mlx_terminate(minirt.canvas.mlx);
	return (0);
} */
#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	800
#define HEIGHT	600
#define N_OBJS	1

void	create_scene1(t_world *world)
{
	t_obj_loader	loader;
	// t_matrix		m[2];

	world->objs = malloc(1 * sizeof(t_shape));
	world->objs_count = 1;
	new_obj_loader(&loader, &world->objs[0]);
	parse_obj_file(&loader, "head.obj");
	world->objs_ext_count += loader.t_count + loader.gp_count;
	// multiply_matrices(scaling(4, 4, 4, &m[0]), rotation_y(cos(M_PI), sin(M_PI), &m[1]),
	// 	&m[0]);
	// set_transform(loader.default_group, &m[0]);
	// set_transform(loader.default_group,
	// 	rotation_y(cos(M_PI - 0.3), sin(M_PI - 0.3), &m));
}

void	create_lights1(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	new_point(-45, 45, -45, &p);
	new_color(0.6, 0.6, 0.6, &c);
	new_light(&p, &c, &world->lights[0]);
	new_point(45, -15, 45, &p);
	new_color(0.6, 0.6, 0.6, &c);
	new_light(&p, &c, &world->lights[1]);
}

void	create_camera1(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;
	t_matrix	m;

	new_camera(camera, WIDTH, HEIGHT, M_PI_4);
	new_point(0, 0, 1, &from);
	new_point(0, 0, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up, &m));
}

void	render_teapot(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	create_lights1(&rt.world);
	create_camera1(&rt.camera);
	create_scene1(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 15");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free_world(&rt.world);
	mlx_terminate(rt.canvas.mlx);
}

int	main(void)
{
	render_teapot();
	return (0);
}
