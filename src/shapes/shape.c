#include "shapes.h"

t_shape	new_shape(void)
{
	return ((t_shape){
		.transform = get_identity_matrix(),
		.inverse = get_identity_matrix(),
		.transpose = get_identity_matrix(),
		.material = new_material(),
		.cast_shadow = true,
		.parent = NULL
	});
}

void	set_transform(t_shape *shape, t_matrix transform)
{
	shape->transform = transform;
	shape->inverse = inverse_matrix(transform);
	shape->transpose = transpose_matrix(shape->inverse);
	shape->is_bounds_precal = false;
}

t_point	world_to_object(t_shape *shape, t_point world_point)
{
	if (shape->parent)
		world_point = world_to_object(shape->parent, world_point);
	return (multiply_matrix_by_tuple(shape->inverse, world_point));
}

t_vector	normal_to_world(t_shape *shape, t_vector object_normal)
{
	object_normal = multiply_matrix_by_tuple(shape->transpose, object_normal);
	object_normal.w = 0.0;
	object_normal = normalize(object_normal);
	if (shape->parent)
		object_normal = normal_to_world(shape->parent, object_normal);
	return (object_normal);
}

t_vector	normal_at(t_shape *shape, t_point world_point)
{
	t_point		object_point;
	t_vector	object_normal;
	t_vector	world_normal;

	object_point = world_to_object(shape, world_point);
	object_normal = shape->normal_at(shape, object_point);
	world_normal = normal_to_world(shape, object_normal);
	return (world_normal);
}
