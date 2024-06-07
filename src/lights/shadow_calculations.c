#include "lights.h"
#include "world.h"

t_point	*point_on_light(t_light *light, double u, double v, t_point *p)
{
	t_tuple	tmp;

	add(&light->corner, add(multiply(&light->uvec,
				u + next_sequence(&light->jitter_by), p), multiply(&light->vvec,
				v + next_sequence(&light->jitter_by), &tmp), &tmp), p);
	return (p);
}

bool	is_shadowed(t_world *world, t_point *light_pos, t_point *point)
{
	t_vector	v;
	double		distance;
	t_ray		r;
	t_hit		*xs;
	t_hit		*h;

	subtract(light_pos, point, &v);
	distance = sqrt(magnitude_squared(&v));
	new_ray(point, normalize(&v, &v), &r);
	xs = intersect_world(world, &r);
	h = hit(xs);
	if (h && h->obj->cast_shadow == true && h->t < distance)
		return (true);
	return (false);
}

double	intensity_at(t_world *world, t_point *point, int index)
{
	double	total;
	double	u;
	double	v;
	t_point	light_position;

	if (world->lights[index].is_area_light == false)
	{
		if (is_shadowed(world, &world->lights[index].position, point))
			return (0.0);
		return (1.0);
	}
	total = 0.0;
	v = -1;
	while (++v < world->lights[index].vsteps)
	{
		u = -1;
		while (++u < world->lights[index].usteps)
		{
			point_on_light(&world->lights[index], u, v, &light_position);
			if (!is_shadowed(world, &light_position, point))
				total += 1.0;
		}
	}
	return (total / world->lights[index].samples);
}
