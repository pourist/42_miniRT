#include "matrices.h"



t_matrix	new_matrix(const double table[MAX][MAX], size_t size)
{
	t_matrix	m;

	m.size = size;
	ft_memmove(m.mx, table, sizeof(double) * SIZE);
	return (m);
}
