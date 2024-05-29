#include "tuples.h"
#include "utils.h"

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
	double	magnitude;
	double	inverse_magnitude;

	magnitude = sqrt(magnitude_squared(a));
	if (eq_dbl(0, magnitude))
		return ((t_vector){0, 0, 0, 0});
	inverse_magnitude = 1.0 / magnitude;
	return ((t_vector){
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

t_tuple	reflect(t_vector in, t_vector normal)
{
	return (subtract(in, multiply(normal, 2.0 * dot(in, normal))));
}
