#include "patterns.h"

static t_color	ring_at(t_pattern *pattern, t_point *world_point);

t_pattern	new_ring_pattern(t_color a, t_color b)
{
	t_pattern	pattern;

	pattern = new_pattern();
	pattern.a = a;
	pattern.b = b;
	pattern.pattern_at = ring_at;
	pattern.has_pattern = true;
	return (pattern);
}

static t_color	ring_at(t_pattern *pattern, t_point *world_point)
{
	double	distance;

	distance = sqrt(world_point->x * world_point->x
			+ world_point->z * world_point->z);
	if ((int)floor(distance) & 1)
		return (pattern->b);
	return (pattern->a);
}
