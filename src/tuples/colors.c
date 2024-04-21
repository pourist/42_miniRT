#include "tuples.h"

t_color	color(double r, double g, double b)
{
	return ((t_color){
		r,
		g,
		b,
	});
}

t_color	add_color(t_color c1, t_color c2)
{
	return ((t_color){
		c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b,
	});
}

t_color	subtract_color(t_color c1, t_color c2)
{
	return ((t_color){
		c1.r - c2.r,
		c1.g - c2.g,
		c1.b - c2.b,
	});
}

t_color	multiply_color(t_color c, double scalar)
{
	return ((t_color){
		c.r * scalar,
		c.g	* scalar,
		c.b * scalar,
	});
}

t_color	hadamard_product(t_color c1, t_color c2)
{
	return ((t_color){
		c1.r * c2.r,
		c1.g * c2.g,
		c1.b * c2.b,
	});
}
