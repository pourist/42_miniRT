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
	t_intersect_tri_params	p;

	p.dir_cross_e2 = cross(r.direction, shape->tri.e2);
	p.det = dot(shape->tri.e1, p.dir_cross_e2);
	if (fabs(p.det) < EPSILON)
		return (false);
	p.f = 1.0 / p.det;
	p.p1_to_origin = subtract(r.origin, shape->tri.p1);
	p.u = p.f * dot(p.p1_to_origin, p.dir_cross_e2);
	if (p.u < 0.0 || p.u > 1.0)
		return (false);
	p.origin_cross_e1 = cross(p.p1_to_origin, shape->tri.e1);
	p.v = p.f * dot(r.direction, p.origin_cross_e1);
	if (p.v < 0.0 || p.u + p.v > 1.0)
		return (false);
	p.t = p.f * dot(shape->tri.e2, p.origin_cross_e1);
	insert_intersection(xs, intersection(p.t, shape));
	return (true);
}
