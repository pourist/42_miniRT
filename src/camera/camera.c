#include "camera.h"

t_camera	new_camera(double hsize, double vsize, double fov)
{
	t_camera	camera;
	double		aspect;
	double		half_view;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.fov = fov;
	camera.transform = get_identity_matrix();
	camera.inverse = camera.transform;
	camera.transpose = camera.transform;
	half_view = tan(camera.fov / 2.0);
	aspect = hsize / vsize;
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2.0) / hsize;
	return (camera);
}

t_ray	ray_for_pixel(t_camera *camera, double px, double py)
{
	double		world_x;
	double		world_y;
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	world_x = camera->half_width - ((px + 0.5) * camera->pixel_size);
	world_y = camera->half_height - ((py + 0.5) * camera->pixel_size);
	pixel = multiply_matrix_by_tuple(camera->inverse,
			new_point(world_x, world_y, -1));
	origin = multiply_matrix_by_tuple(camera->inverse, new_point(0, 0, 0));
	direction = normalize(subtract(pixel, origin));
	return (new_ray(origin, direction));
}

void	set_transform_camera(t_camera *camera, t_matrix transform)
{
	camera->transform = transform;
	camera->inverse = inverse_matrix(transform);
	camera->transpose = transpose_matrix(camera->inverse);
}
