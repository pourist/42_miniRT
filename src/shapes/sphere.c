#include "shapes.h"

t_shape	new_sphere(void)
{
	t_shape	shape;

	shape.sphere.origin = new_point(0, 0, 0);
	shape.sphere.radius = 1.0;
	return (shape);
}
