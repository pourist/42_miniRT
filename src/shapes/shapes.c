#include "shapes.h"

t_shape	new_shape(void)
{
	return ((t_shape){
		.transform = get_identity_matrix(),
		.inverse = get_identity_matrix(),
	});
}

void	set_transform(t_shape *shape, t_matrix transform)
{
	shape->transform = transform;
	shape->inverse = inverse_matrix(transform);
}
