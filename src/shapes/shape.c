#include "shapes.h"

t_shape	new_shape(void)
{
	return ((t_shape){
		.transform = get_identity_matrix(),
		.inverse = get_identity_matrix(),
		.transpose = get_identity_matrix(),
		.material = new_material(),
	});
}

void	set_transform(t_shape *shape, t_matrix transform)
{
	shape->transform = transform;
	shape->inverse = inverse_matrix(transform);
	shape->transpose = transpose_matrix(shape->inverse);
}

t_vector	normal_at(t_shape *shape, t_point world_point)
{
	t_point		object_point;
	t_vector	object_normal;
	t_vector	world_normal;

	object_point = multiply_matrix_by_tuple(shape->inverse, world_point);
	object_normal = shape->normal_at(shape, object_point);
	world_normal = multiply_matrix_by_tuple(shape->transpose, object_normal);
	world_normal.w = 0.0;
	return (normalize(world_normal));
}
