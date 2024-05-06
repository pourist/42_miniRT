#include "patterns.h"
#include <stdio.h>

t_color	solid_at(t_pattern *pattern, t_point *shape_point);

t_pattern	new_solid_pattern(t_color color)
{
	t_pattern	solid;

	solid = new_pattern();
	solid.color = color;
	solid.pattern_at = solid_at;
	solid.has_pattern = false;
	return (solid);
}

t_color	solid_at(t_pattern *pattern, t_point *shape_point)
{
	(void)shape_point;
	return (pattern->color);
}
