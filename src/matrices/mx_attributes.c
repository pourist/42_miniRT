#include "matrices.h"

double	get_determinant(t_matrix m)
{
	double	det;

	det = 0;
	if (m.size == 2)
		det = m.mx[0][0] * m.mx[1][1]
			- m.mx[0][1] * m.mx[1][0];
	return (det);
}

t_matrix	get_submatrix(t_matrix m, int del_row, int del_col)
{
	double	sub_matrix[MAX][MAX];
	int		row;
	int		col;

	row = -1;
	while (++row < m.size - 1)
	{
		col = -1;
		while (++col < m.size - 1)
			sub_matrix[row][col]
				= m.mx[row + (row >= del_row)][col + (col >= del_col)];
	}
	return (new_matrix(sub_matrix, m.size - 1));
}
