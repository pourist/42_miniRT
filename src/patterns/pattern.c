#include "patterns.h"
#include "shapes.h"

t_pattern	new_pattern(void)
{
	return ((t_pattern){
		.a = NULL,
		.b = NULL,
		.transform = get_identity_matrix(),
		.inverse = get_identity_matrix(),
		.transpose = get_identity_matrix(),
	});
}

t_color	pattern_at_shape(t_pattern *pattern, t_shape *shape,
								t_point *world_point)
{
	t_point		shape_point;

	shape_point = multiply_matrix_by_tuple(shape->inverse, *world_point);
	return (pattern->pattern_at(pattern, &shape_point));
}

void	set_pattern_transform(t_pattern *pattern, t_matrix transform)
{
	pattern->transform = transform;
	pattern->inverse = inverse_matrix(transform);
	pattern->transpose = transpose_matrix(pattern->inverse);
}
