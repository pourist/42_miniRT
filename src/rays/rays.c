#include "rays.h"

t_ray	new_ray(t_point	origin, t_point	direction)
{
	return ((t_ray){origin, direction});
}

t_point	position(t_ray r, double t)
{
	return (add(r.origin, multiply(r.direction, t)));
}
