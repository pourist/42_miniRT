#include "shapes.h"

bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray);

t_shape	new_sphere(void)
{
	t_shape	shape;

	shape.sphere.origin = new_point(0, 0, 0);
	shape.sphere.radius = 1.0;
	shape.intersect_fn = intersect_sphere;
	return (shape);
}

static t_discriminant	sphere_discriminant(t_sphere *sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_tuple	sphere_to_ray;

	sphere_to_ray = subtract(ray.origin, sphere->origin);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - (sphere->radius * sphere->radius);
	delta = (b * b) - (4.0 * a * c);
	return ((t_discriminant){
		.a = a,
		.b = b,
		.c = c,
		.t1 = (-b - sqrt(delta)) / (2.0 * a),
		.t2 = (-b + sqrt(delta)) / (2.0 * a),
		.discriminant = delta,
	});
}

bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_discriminant	d;

	d = sphere_discriminant(&shape->sphere, ray);
	if (d.discriminant < 0)
		return (false);
	insert_intersection(xs, intersection(d.t1, shape));
	insert_intersection(xs, intersection(d.t2, shape));
	return (true);
}
