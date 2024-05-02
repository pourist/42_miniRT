#include "shapes.h"

static bool		intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray);
static t_vector	normal_at_sphere(t_shape *sphere, t_point object_point);

t_shape	new_sphere(void)
{
	t_shape	shape;

	shape = new_shape();
	shape.sphere.origin = new_point(0, 0, 0);
	shape.sphere.radius = 1.0;
	shape.intersect_fn = intersect_sphere;
	shape.normal_at = normal_at_sphere;
	// shape.material.diffuse = 0.7;
	// shape.material.specular = 0.3;
	return (shape);
}

static t_discriminant	sphere_discriminant(t_sphere *sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	discrim_and_sqrtd[2];
	t_tuple	sphere_to_ray;

	sphere_to_ray = subtract(ray.origin, sphere->origin);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - (sphere->radius * sphere->radius);
	discrim_and_sqrtd[0] = (b * b) - (4.0 * a * c);
	discrim_and_sqrtd[1] = sqrt(discrim_and_sqrtd[0]);
	return ((t_discriminant){
		a,
		b,
		c,
		.t1 = (-b - discrim_and_sqrtd[1]) / (2.0 * a),
		.t2 = (-b + discrim_and_sqrtd[1]) / (2.0 * a),
		.discriminant = discrim_and_sqrtd[0]});
}

// TODO: check in the future if we dont need the negative values of t1 and t2
// avoid inserting them in the intersection list
static bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_discriminant	d;

	d = sphere_discriminant(&shape->sphere, ray);
	if (d.discriminant < 0)
		return (false);
	insert_intersection(xs, intersection(d.t1, shape));
	insert_intersection(xs, intersection(d.t2, shape));
	return (true);
}

static t_vector	normal_at_sphere(t_shape *sphere, t_point object_point)
{
	(void)sphere;
	return (subtract(object_point, sphere->sphere.origin));
}
