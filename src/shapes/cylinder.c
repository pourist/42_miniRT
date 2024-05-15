#include "shapes.h"

static bool		intersect_cylinder(t_hit **xs, t_shape *cyl, t_ray r);
static t_vector	normal_at_cylinder(t_shape *shape, t_point object_point);

t_shape	new_cylinder(void)
{
	t_shape	shape;

	shape = new_shape();
	shape.cyl.origin = new_point(0, 0, 0);
	shape.cyl.radius = 1.0;
	shape.cyl.min = -INFINITY;
	shape.cyl.max = INFINITY;
	shape.intersect_fn = intersect_cylinder;
	shape.normal_at = normal_at_cylinder;
	shape.cyl.closed = false;
	return (shape);
}

static bool	check_cap(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return (x * x + z * z <= 1.0);
}

static void	intersect_caps(t_hit **xs, t_shape *shape, t_ray *ray)
{
	double			t;

	if (!shape->cyl.closed || fabs(ray->direction.y) < EPSILON)
		return ;
	t = (shape->cyl.min - ray->origin.y) / ray->direction.y;
	if (check_cap(ray, t))
		insert_intersection(xs, intersection(t, shape));
	t = (shape->cyl.max - ray->origin.y) / ray->direction.y;
	if (check_cap(ray, t))
		insert_intersection(xs, intersection(t, shape));
}

static bool	intersect_cylinder(t_hit **xs, t_shape *shape, t_ray r)
{
	t_discriminant	d;
	double			sqrt_d;
	double			y_pos;

	intersect_caps(xs, shape, &r);
	d.a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;
	if (fabs(d.a) < EPSILON)
		return (false);
	d.b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	d.c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
	d.discriminant = (d.b * d.b) - (4 * d.a * d.c);
	if (d.discriminant < 0.0)
		return (false);
	sqrt_d = sqrt(d.discriminant);
	d.t1 = (-d.b - sqrt_d) / (2 * d.a);
	d.t2 = (-d.b + sqrt_d) / (2 * d.a);
	if (d.t1 > d.t2)
		ft_swap(&d.t1, &d.t2);
	y_pos = r.origin.y + d.t1 * r.direction.y;
	if (shape->cyl.min < y_pos && y_pos < shape->cyl.max)
		insert_intersection(xs, intersection(d.t1, shape));
	y_pos = r.origin.y + d.t2 * r.direction.y;
	if (shape->cyl.min < y_pos && y_pos < shape->cyl.max)
		insert_intersection(xs, intersection(d.t2, shape));
	return (true);
}

static t_vector	normal_at_cylinder(t_shape *shape, t_point object_point)
{
	double	dist;

	dist = object_point.x * object_point.x + object_point.z * object_point.z;
	if (dist < 1.0 && object_point.y >= shape->cyl.max - EPSILON)
		return (new_vector(0, 1, 0));
	else if (dist < 1.0 && object_point.y <= shape->cyl.min + EPSILON)
		return (new_vector(0, -1, 0));
	else
		return (new_vector(object_point.x, 0, object_point.z));
}
