#include "shapes.h"

static bool		intersect_cylinder(t_hit **xs, t_shape *cyl, t_ray ray);
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
	return (shape);
}

static bool	intersect_cylinder(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_discriminant	d;
	double			sqrt_d;
	double			y_pos;

	d.a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	if (d.a < EPSILON && d.a > -EPSILON)
		return (false);
	d.b = (2.0 * ray.origin.x * ray.direction.x)
		+ (2.0 * ray.origin.z * ray.direction.z);
	d.c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;
	d.discriminant = (d.b * d.b) - (4 * d.a * d.c);
	if (d.discriminant < 0)
		return (false);
	sqrt_d = sqrt(d.discriminant);
	d.t1 = (-d.b - sqrt_d) / (2 * d.a);
	d.t2 = (-d.b + sqrt_d) / (2 * d.a);
	if (d.t1 > d.t2)
		ft_swap(&d.t1, &d.t2);
	y_pos = ray.origin.y + d.t1 * ray.direction.y;
	if (shape->cyl.min < y_pos && y_pos < shape->cyl.max)
		insert_intersection(xs, intersection(d.t1, shape));
	y_pos = ray.origin.y + d.t2 * ray.direction.y;
	if (shape->cyl.min < y_pos && y_pos < shape->cyl.max)
		insert_intersection(xs, intersection(d.t2, shape));
	return (true);
}

static t_vector	normal_at_cylinder(t_shape *shape, t_point object_point)
{
	(void)shape;
	return (new_vector(object_point.x, 0, object_point.z));
}
