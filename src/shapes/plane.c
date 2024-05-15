#include "shapes.h"

static t_vector	normal_at_plain(t_shape *plane, t_point local_point);
static bool	intersect_plane(t_hit **xs, t_shape *shape, t_ray ray);

t_shape	new_plane(void)
{
	t_shape	shape;

	shape = new_shape();
	shape.normal_at = normal_at_plain;
	shape.intersect_fn = intersect_plane;
	shape.plane.origin = new_point(0, 0, 0);
	return (shape);
}

static t_vector	normal_at_plain(t_shape *plane, t_point local_point)
{
	(void)local_point;
	(void)plane;
	return (new_vector(0, 1, 0));
}

static bool	intersect_plane(t_hit **xs, t_shape *shape, t_ray ray)
{
	double	t;

	if (fabs(ray.direction.y) < EPSILON)
		return (false);
	t = -ray.origin.y / ray.direction.y;
	insert_intersection(xs, intersection(t, shape));
	return (true);
}
