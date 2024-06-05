#include "shapes.h"
#include "groups.h"

static bool		intersect_cone(t_hit **xs, t_shape *shape, t_ray *r);
static t_vector	normal_at_cone(t_shape *shape, t_point *local_point);

t_shape	*new_cone(t_shape *shape)
{
	new_shape(shape);
	shape->cone.origin = new_point(0, 0, 0);
	shape->cone.min = -MAXFLOAT;
	shape->cone.max = MAXFLOAT;
	shape->cone.closed = false;
	shape->intersect_fn = intersect_cone;
	shape->normal_at = normal_at_cone;
	shape->bounds_of = cone_bounds;
	return (shape);
}

static bool	check_cap(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return ((x * x) + (z * z)
		<= fabs(ray->origin.y + t * ray->direction.y));
}

static void	intersect_caps(t_hit **xs, t_shape *shape, t_ray *r)
{
	double			t;

	if (!shape->cone.closed || eq_dbl(r->direction.y, 0.0))
		return ;
	t = (shape->cone.min - r->origin.y) / r->direction.y;
	if (check_cap(r, t))
		insert_intersection(xs, intersection(t, shape));
	t = (shape->cone.max - r->origin.y) / r->direction.y;
	if (check_cap(r, t))
		insert_intersection(xs, intersection(t, shape));
}

static bool	intersect_cone(t_hit **xs, t_shape *shape, t_ray *r)
{
	t_intersect_params	p;
	double				y_pos;

	intersect_caps(xs, shape, r);
	cone_discriminant(r, &p);
	if (eq_dbl(0, p.a))
	{
		if (eq_dbl(0, p.b))
			return (false);
		insert_intersection(xs, intersection((-p.c) / (2 * p.b), shape));
		return (true);
	}
	if (p.discriminant < 0)
		return (false);
	if (p.t1 > p.t2)
		ft_swap(&p.t1, &p.t2);
	y_pos = r->origin.y + p.t2 * r->direction.y;
	if (shape->cone.min < y_pos && y_pos < shape->cone.max)
		insert_intersection(xs, intersection(p.t2, shape));
	y_pos = r->origin.y + p.t1 * r->direction.y;
	if (shape->cone.min < y_pos && y_pos < shape->cone.max)
		insert_intersection(xs, intersection(p.t1, shape));
	return (true);
}

static t_vector	normal_at_cone(t_shape *shape, t_point *local_point)
{
	double	dist;
	double	y;

	dist = (local_point->x * local_point->x)
		+ (local_point->z * local_point->z);
	if (dist < 1.0 && local_point->y >= shape->cone.max - EPSILON)
		return (new_vector(0, 1, 0));
	else if (dist < 1.0 && local_point->y <= shape->cone.min + EPSILON)
		return (new_vector(0, -1, 0));
	else
	{
		y = sqrt(dist);
		if (local_point->y > 0.0)
			y = -y;
		return (new_vector(local_point->x, y, local_point->z));
	}
}
