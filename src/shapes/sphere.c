#include "shapes.h"
#include "groups.h"

static bool		intersect_sphere(t_hit **xs, t_shape *shape, t_ray r);
static t_vector	normal_at_sphere(t_shape *sphere, t_point local_point);

t_shape	new_sphere(void)
{
	t_shape	shape;

	shape = new_shape();
	shape.sphere.origin = new_point(0, 0, 0);
	shape.sphere.radius = 1.0;
	shape.intersect_fn = intersect_sphere;
	shape.normal_at = normal_at_sphere;
	shape.material.diffuse = 0.8;
	shape.material.specular = 0.5;
	shape.bounds_fn = sphere_bounds;
	return (shape);
}

t_shape	new_glass_sphere(void)
{
	t_shape	shape;

	shape = new_sphere();
	shape.material.transparency = 1.0;
	shape.material.refractive_index = GLASS;
	return (shape);
}

static bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray r)
{
	t_discriminant	d;
	t_vector		sphere_to_ray;
	double			sqrt_d;

	sphere_to_ray = subtract(r.origin, shape->sphere.origin);
	d.a = dot(r.direction, r.direction);
	d.b = 2.0 * dot(r.direction, sphere_to_ray);
	d.c = dot(sphere_to_ray, sphere_to_ray) - 1.0;
	d.discriminant = pow(d.b, 2) - (4.0 * d.a * d.c);
	if (d.discriminant < 0.0)
		return (false);
	sqrt_d = sqrt(d.discriminant);
	d.t1 = (-d.b - sqrt_d) / (2.0 * d.a);
	d.t2 = (-d.b + sqrt_d) / (2.0 * d.a);
	insert_intersection(xs, intersection(d.t1, shape));
	if (d.discriminant != 0.0)
		insert_intersection(xs, intersection(d.t2, shape));
	return (true);
}

static t_vector	normal_at_sphere(t_shape *sphere, t_point local_point)
{
	(void)sphere;
	return (subtract(local_point, sphere->sphere.origin));
}
