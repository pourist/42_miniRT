#include "tuples.h"

t_color	new_color(double r, double g, double b, double a)
{
	return ((t_color){
		r,
		g,
		b,
		a,
	});
}

t_color	add_color(t_color c1, t_color c2)
{
	return ((t_color){
		c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b,
		c1.a + c2.a,
	});
}

t_color	subtract_color(t_color c1, t_color c2)
{
	return ((t_color){
		c1.r - c2.r,
		c1.g - c2.g,
		c1.b - c2.b,
		c1.a - c2.a,
	});
}

t_color	multiply_color(t_color c, double scalar)
{
	if (scalar == 0.0)
		return ((t_color){0.0, 0.0, 0.0, 0.0});
	else if (scalar == 1.0)
		return (c);
	return ((t_color){
		c.r * scalar,
		c.g * scalar,
		c.b * scalar,
		c.a * scalar,
	});
}

t_color	hadamard_product(t_color c1, t_color c2)
{
	return ((t_color){
		c1.r * c2.r,
		c1.g * c2.g,
		c1.b * c2.b,
		c1.a * c2.a,
	});
}
