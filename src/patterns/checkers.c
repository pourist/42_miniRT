#include "patterns.h"

static t_color	checkers_at(t_pattern *pattern, t_point *world_point);

t_pattern	new_checkers_pattern(t_color a, t_color b)
{
	t_pattern	pattern;

	pattern = new_pattern();
	pattern.a = a;
	pattern.b = b;
	pattern.pattern_at = checkers_at;
	pattern.has_pattern = true;
	return (pattern);
}

static t_color	checkers_at(t_pattern *pattern, t_point *world_point)
{
	if (((int)floor(world_point->x) + (int)floor(world_point->y)
			+ (int)floor(world_point->z)) & 1)
		return (pattern->b);
	return (pattern->a);
}
