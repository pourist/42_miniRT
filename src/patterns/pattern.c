#include "patterns.h"
#include "shapes.h"

t_pattern	new_pattern(void)
{
	return ((t_pattern){
		.transform = get_identity_matrix(),
		.inverse = get_identity_matrix(),
		.transpose = get_identity_matrix(),
	});
}

t_color	pattern_at_shape(t_pattern *pattern, t_shape *shape,
								t_point *world_point)
{
	t_point		object_point;
	t_point		pattern_point;

	object_point = multiply_matrix_by_tuple(shape->inverse, *world_point);
	pattern_point = multiply_matrix_by_tuple(pattern->inverse, object_point);
	return (pattern->pattern_at(pattern, &pattern_point));
}
