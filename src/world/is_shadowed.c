#include "world.h"

bool	is_shadowed(t_world *world, t_point *point, int index)
{
	t_vector	v;
	double		distance;
	t_ray		r;
	t_hit		*xs;
	t_hit		*h;

	v = subtract(world->lights[index].position, *point);
	distance = sqrt(magnitude_squared(v));
	r = new_ray(*point, normalize(v));
	xs = intersect_world(world, &r);
	h = hit(xs);
	if (h && h->t < distance)
		return (true);
	return (false);
}
