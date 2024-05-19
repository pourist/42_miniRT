#include "shapes.h"
#include "groups.h"

static bool		intersect_cone(t_hit **xs, t_shape *shape, t_ray r);
static t_vector	normal_at_cone(t_shape *shape, t_point local_point);

t_shape	new_cone(void)
{
	t_shape	shape;

	shape = new_shape();
	shape.cone.origin = new_point(0, 0, 0);
	shape.cone.min = -INFINITY;
	shape.cone.max = INFINITY;
	shape.intersect_fn = intersect_cone;
	shape.normal_at = normal_at_cone;
	shape.cone.closed = false;
	shape.bounds_fn = cone_bounds;
	return (shape);
}

static bool	check_cap(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return (pow(x, 2) + pow(z, 2)
		<= fabs(ray->origin.y + t * ray->direction.y));
}

static void	intersect_caps(t_hit **xs, t_shape *shape, t_ray *ray)
{
	double			t;

	if (!shape->cone.closed || fabs(ray->direction.y) < EPSILON)
		return ;
	t = (shape->cone.min - ray->origin.y) / ray->direction.y;
	if (check_cap(ray, t))
		insert_intersection(xs, intersection(t, shape));
	t = (shape->cone.max - ray->origin.y) / ray->direction.y;
	if (check_cap(ray, t))
		insert_intersection(xs, intersection(t, shape));
}

static bool	intersect_cone(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_discriminant	d;
	double			y_pos;

	intersect_caps(xs, shape, &ray);
	cone_discriminant(&ray, &d);
	if (fabs(d.a) < EPSILON)
	{
		if (fabs(d.b) < EPSILON)
			return (false);
		insert_intersection(xs, intersection((-d.c) / (2.0 * d.b), shape));
		return (true);
	}
	if (d.discriminant < 0.0)
		return (false);
	if (d.t1 > d.t2)
		ft_swap(&d.t1, &d.t2);
	y_pos = ray.origin.y + d.t2 * ray.direction.y;
	if (shape->cone.min < y_pos && y_pos < shape->cone.max)
		insert_intersection(xs, intersection(d.t2, shape));
	y_pos = ray.origin.y + d.t1 * ray.direction.y;
	if (shape->cone.min < y_pos && y_pos < shape->cone.max)
		insert_intersection(xs, intersection(d.t1, shape));
	return (true);
}

static t_vector	normal_at_cone(t_shape *shape, t_point local_point)
{
	double	dist;
	double	y;

	dist = pow(local_point.x, 2) + pow(local_point.z, 2);
	if (dist < 1.0 && local_point.y >= shape->cone.max - EPSILON)
		return (new_vector(0, 1, 0));
	else if (dist < 1.0 && local_point.y <= shape->cone.min + EPSILON)
		return (new_vector(0, -1, 0));
	else
	{
		y = sqrt(dist);
		if (local_point.y > 0.0)
			y = -y;
		return (new_vector(local_point.x, y, local_point.z));
	}
}
