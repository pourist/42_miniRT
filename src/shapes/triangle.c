#include "shapes.h"

static	t_vector	normal_at_triangle(t_shape *shape, t_point local_point);
static bool		intersect_triangle(t_hit **xs, t_shape *shape, t_ray r);

t_shape	new_triangle(t_point p1, t_point p2, t_point p3)
{
	t_shape	shape;

	shape = new_shape();
	shape.tri.p1 = p1;
	shape.tri.p2 = p2;
	shape.tri.p3 = p3;
	shape.tri.e1 = subtract(p2, p1);
	shape.tri.e2 = subtract(p3, p1);
	shape.tri.normal = normalize(cross(shape.tri.e2, shape.tri.e1));
	shape.normal_at = normal_at_triangle;
	shape.intersect_fn = intersect_triangle;
	return (shape);
}

static	t_vector	normal_at_triangle(t_shape *shape, t_point local_point)
{
	(void)local_point;
	return (shape->tri.normal);
}

static bool	intersect_triangle(t_hit **xs, t_shape *shape, t_ray r)
{
	t_vector	dir_cross_e2;
	double		det;
	double		f;
	t_point		p1_to_origin;
	double		u;
	t_vector	origin_cross_e1;
	double		v;
	double		t;

	dir_cross_e2 = cross(r.direction, shape->tri.e2);
	det = dot(shape->tri.e1, dir_cross_e2);
	if (fabs(det) < EPSILON)
		return (false);
	f = 1.0 / det;
	p1_to_origin = subtract(r.origin, shape->tri.p1);
	u = f * dot(p1_to_origin, dir_cross_e2);
	if (u < 0.0 || u > 1.0)
		return (false);
	origin_cross_e1 = cross(p1_to_origin, shape->tri.e1);
	v = f * dot(r.direction, origin_cross_e1);
	if (v < 0.0 || u + v > 1.0)
		return (false);
	t = f * dot(shape->tri.e2, origin_cross_e1);
	insert_intersection(xs, intersection(t, shape));
	return (true);
}
