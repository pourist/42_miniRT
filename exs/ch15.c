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
	parse_obj_file(&loader, "../obj_files/teapot_low.obj");
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
	from = new_point(0, 20, -35);
	to = new_point(0, 0, 0);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

void	render_teapot(void)
{
	t_world		world;
	t_camera	camera;
	t_canvas	canvas;

	world = new_world();
	create_lights1(&world);
	create_camera1(&camera);
	create_scene1(&world);
	render(&canvas, &world, &camera);
	mlx_image_to_window(canvas.mlx, canvas.img, 0, 0);
	mlx_close_hook(canvas.mlx, &quit, &canvas);
	mlx_key_hook(canvas.mlx, &handle_keyhook, &canvas);
	mlx_loop(canvas.mlx);
	free_world(&world);
	mlx_terminate(canvas.mlx);
}

int	main(void)
{
	render_teapot();
	return (0);
}
