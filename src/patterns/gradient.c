#include "patterns.h"

static t_color	gradient_at(t_pattern *pattern, t_point *world_point);

t_pattern	new_gradient_pattern(t_color a, t_color b)
{
	t_pattern	pattern;

	pattern = new_pattern();
	pattern.a = a;
	pattern.b = b;
	pattern.pattern_at = gradient_at;
	pattern.has_pattern = true;
	return (pattern);
}

static t_color	gradient_at(t_pattern *pattern, t_point *world_point)
{
	t_color		distance;
	double		fraction;

	distance = subtract_color(pattern->b, pattern->a);
	fraction = world_point->x - floor(world_point->x);
	return (add_color(pattern->a, multiply_color(distance, fraction)));
}
