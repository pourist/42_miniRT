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

double	magnitude_squared(t_vector a)
{
	return (
		a.x * a.x
		+ a.y * a.y
		+ a.z * a.z
		+ a.w * a.w
	);
}

t_vector	normalize(t_vector a)
{
	double	sqrt_magnitude;
	double	inverse_magnitude;

	sqrt_magnitude = magnitude_squared(a);
	if (sqrt_magnitude == 0)
		return (a);
	inverse_magnitude = 1.0 / sqrt(sqrt_magnitude);
	return ((t_tuple){
		a.x * inverse_magnitude,
		a.y * inverse_magnitude,
		a.z * inverse_magnitude,
		a.w * inverse_magnitude,
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
	return (new_vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		));
}
