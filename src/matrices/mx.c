#include "matrices.h"

bool	is_eq_mx(t_matrix m1, t_matrix m2)
{
	return (ft_memcmp(m1.mx, m2.mx, sizeof(double) * SIZE) == 0);
}

t_matrix	new_matrix(const double table[MAX][MAX], size_t size)
{
	t_matrix	m;

	m.size = size;
	ft_memmove(m.mx, table, sizeof(double) * SIZE);
	return (m);
}
