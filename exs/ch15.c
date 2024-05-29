#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	600
#define HEIGHT	480
#define N_OBJS	1

void	create_scene1(t_world *world)
{
	t_obj_loader	loader;

	world->objs = malloc(1 * sizeof(t_shape));
	world->objs_count = 1;
	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/teapot.obj");
	set_transform(&loader.default_group,
		rotation_x(cos(-M_PI / 2.0), sin(-M_PI / 2.0)));
	world->objs[0] = loader.default_group;
}

void	create_lights1(t_world *world)
{
	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	world->lights[0] = new_light(new_point(-45, -45, -45), new_color(0.3, 0.6, 0.95));
	world->lights[1] = new_light(new_point(45, 15, -45), new_color(0.95, 0.6, 0.3));
}

void	create_camera1(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 3.0);
	from = new_point(0, 15, -45);
	to = new_point(0, 10, 0);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

void	render_teapot(void)
{
	t_mini_rt	rt;

	rt.world = new_world();
	create_lights1(&rt.world);
	create_camera1(&rt.camera);
	create_scene1(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 15");
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
