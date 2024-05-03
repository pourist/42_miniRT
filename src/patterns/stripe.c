#include "patterns.h"

static t_color	stripe_at(t_pattern *pattern, t_point *world_point);

t_pattern	new_stripe_pattern(t_color a, t_color b)
{
	t_pattern	pattern;

	pattern = new_pattern();
	pattern.a = a;
	pattern.b = b;
	pattern.pattern_at = stripe_at;
	pattern.has_pattern = true;
	return (pattern);
}

static t_color	stripe_at(t_pattern *pattern, t_point *world_point)
{
	if (((int)floor(world_point->x)) & 1)
		return (pattern->b);
	return (pattern->a);
}
