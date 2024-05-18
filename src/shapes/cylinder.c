#include "shapes.h"
#include "groups.h"

static bool		intersect_cylinder(t_hit **xs, t_shape *cyl, t_ray r);
static t_vector	normal_at_cylinder(t_shape *shape, t_point local_point);

t_shape	new_cylinder(void)
{
	t_shape	shape;

	shape = new_shape();
	shape.cyl.origin = new_point(0, 0, 0);
	shape.cyl.min = -INFINITY;
	shape.cyl.max = INFINITY;
	shape.intersect_fn = intersect_cylinder;
	shape.normal_at = normal_at_cylinder;
	shape.cyl.closed = false;
	shape.bounds_fn = cylinder_bounds;
	shape.is_bounds_precal = false;
	return (shape);
}

static bool	check_cap(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return (pow(x, 2) + pow(z, 2) <= 1.0);
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
	double			y_pos;

	intersect_caps(xs, shape, &r);
	cylinder_discriminant(&r, &d);
	if (fabs(d.a) < EPSILON || d.discriminant < 0.0)
		return (false);
	if (d.t1 > d.t2)
		ft_swap(&d.t1, &d.t2);
	y_pos = r.origin.y + d.t2 * r.direction.y;
	if (shape->cyl.min < y_pos && y_pos < shape->cyl.max)
		insert_intersection(xs, intersection(d.t2, shape));
	y_pos = r.origin.y + d.t1 * r.direction.y;
	if (shape->cyl.min < y_pos && y_pos < shape->cyl.max)
		insert_intersection(xs, intersection(d.t1, shape));
	return (true);
}

static t_vector	normal_at_cylinder(t_shape *shape, t_point local_point)
{
	double	dist;

	dist = pow(local_point.x, 2) + pow(local_point.z, 2);
	if (dist < 1.0 && local_point.y >= shape->cyl.max - EPSILON)
		return (new_vector(0, 1, 0));
	else if (dist < 1.0 && local_point.y <= shape->cyl.min + EPSILON)
		return (new_vector(0, -1, 0));
	else
		return (new_vector(local_point.x, 0, local_point.z));
}
