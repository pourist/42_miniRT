#include "matrices.h"

t_matrix	multiply_matrices(t_matrix m1, t_matrix m2)
{
	double	result[MAX][MAX];
	int		row;
	int		col;

	row = -1;
	while (++row < MAX)
	{
		col = -1;
		while (++col < MAX)
		{
			result[row][col] = m1.mx[row][0] * m2.mx[0][col]
				+ m1.mx[row][1] * m2.mx[1][col]
				+ m1.mx[row][2] * m2.mx[2][col]
				+ m1.mx[row][3] * m2.mx[3][col];
		}
	}
	return (new_matrix(result, MAX));
}

t_tuple	multiply_matrix_by_tuple(t_matrix m, t_tuple t)
{
	double	result[MAX];
	int		row;

	row = -1;
	while (++row < MAX)
	{
		result[row] = m.mx[row][0] * t.x
			+ m.mx[row][1] * t.y
			+ m.mx[row][2] * t.z
			+ m.mx[row][3] * t.w;
	}
	return (new_tuple(result[0], result[1], result[2], result[3]));
}

t_matrix	transpose_matrix(t_matrix m)
{
	double	result[MAX][MAX];
	int		row;
	int		col;

	row = -1;
	while (++row < m.size)
	{
		col = -1;
		while (++col < m.size)
			result[col][row] = m.mx[row][col];
	}
	return (new_matrix(result, m.size));
}
