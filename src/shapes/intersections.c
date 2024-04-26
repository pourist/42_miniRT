#include "shapes.h"

void	intersect(t_intersect *xs, t_shape *s, t_ray ray)
{
	t_vector	sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		delta;

	sphere_to_ray = subtract(ray.origin, s->sphere.origin);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - 1;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		xs->count = 0;
	else
	{
		xs->t[0] = (-b - sqrt(delta)) / (2 * a);
		xs->t[1] = (-b + sqrt(delta)) / (2 * a);
		xs->count = 2;
	}
}
