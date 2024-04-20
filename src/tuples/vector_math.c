#include "tuples.h"

double	magnitude(t_vector a)
{
	return (sqrt(
			a.x * a.x
			+ a.y * a.y
			+ a.z * a.z
			+ a.w * a.w
		));
}

t_vector	normalize(t_vector a)
{
	double	length;

	length = magnitude(a);
	return ((t_tuple){
		a.x / length,
		a.y / length,
		a.z / length,
		a.w / length,
	});
}

double	dot(t_vector a, t_vector b)
{
	return (
		a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w
	);
}

t_vector	cross(t_vector a, t_vector b)
{
	return (vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		));
}
