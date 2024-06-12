#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	1080
#define HEIGHT 720

void	create_scene(t_world *world)
{
	t_shape	s;

	world->objs = malloc(1 * sizeof(t_shape));
	world->objs_count = 1;
	new_sphere(&s);
	new_uv_checkers_pattern(new_solid_pattern(new_color(0, 0.5, 0)),
		new_solid_pattern(new_color(1, 1, 1)), &s.material.pattern);
	s.material.specular = 0.4;
	s.material.shininess = 10;
	s.material.diffuse = 0.6;
	world->objs[0] = s;
}

void	create_lights(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(1 * sizeof(t_light));
	world->lights_count = 1;
	new_point(-10, 10, -10, &p);
	c = new_color(1, 1, 1);
	new_light(&p, &c, &world->lights[0]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI_2);
	new_point(0, 0, -5, &from);
	new_point(0, 0, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&camera->transform));
}

int	main(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	create_lights(&rt.world);
	create_camera(&rt.camera);
	create_scene(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Bonus texture mapping");
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
