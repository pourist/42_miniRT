#include "patterns.h"

static t_color	checkers_at(t_pattern *pattern, t_point *shape_point);

t_pattern	new_checkers_pattern(t_pattern a, t_pattern b)
{
	t_pattern	pattern;

	pattern = new_pattern();
	pattern.a = malloc(sizeof(t_pattern));
	if (!pattern.a)
		return (pattern);
	pattern.b = malloc(sizeof(t_pattern));
	if (!pattern.b)
		return (pattern);
	*pattern.a = a;
	*pattern.b = b;
	pattern.pattern_at = checkers_at;
	pattern.has_pattern = true;
	return (pattern);
}

static t_color	checkers_at(t_pattern *pattern, t_point *shape_point)
{
	t_point	pattern_point;

	pattern_point = multiply_matrix_by_tuple(pattern->inverse, *shape_point);
	if (((int)floor(pattern_point.x) + (int)floor(pattern_point.y)
			+ (int)floor(pattern_point.z)) & 1)
		return (pattern->b->pattern_at(pattern->b, &pattern_point));
	return (pattern->a->pattern_at(pattern->a, &pattern_point));
}
