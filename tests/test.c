#include "test.h"

bool	matrix_eq(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	if (a.size != b.size)
		return (false);
	i = -1;
	while (++i < a.size)
	{
		j = -1;
		while (++j < a.size)
			if (a.mx[i][j] - b.mx[i][j] > EPSILON
				|| a.mx[i][j] - b.mx[i][j] < -EPSILON)
				return (false);
	}
	return (true);
}

bool	tuple_eq(t_tuple a, t_tuple b)
{
	if (a.x - b.x > EPSILON || a.x - b.x < -EPSILON)
		return (false);
	if (a.y - b.y > EPSILON || a.y - b.y < -EPSILON)
		return (false);
	if (a.z - b.z > EPSILON || a.z - b.z < -EPSILON)
		return (false);
	if (a.w - b.w > EPSILON || a.w - b.w < -EPSILON)
		return (false);
	return (true);
}

bool	color_eq(t_color a, t_color b)
{
	if (a.r - b.r > EPSILON || a.r - b.r < -EPSILON)
		return (false);
	if (a.g - b.g > EPSILON || a.g - b.g < -EPSILON)
		return (false);
	if (a.b - b.b > EPSILON || a.b - b.b < -EPSILON)
		return (false);
	if (a.a - b.a > EPSILON || a.a - b.a < -EPSILON)
		return (false);
	return (true);
}
