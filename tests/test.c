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
