#include "test.h"

Test(matrices, create_4x4_matrix)
{
	t_matrix	m;
	const double	table[MAX][MAX] = {
		{1, 2, 3, 4},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5},
	};

	m = new_matrix(table, MAX);
	cr_assert(eq(dbl, m.mx[0][0], 1));
	cr_assert(eq(dbl, m.mx[0][1], 2));
	cr_assert(eq(dbl, m.mx[0][2], 3));
	cr_assert(eq(dbl, m.mx[0][3], 4));

	cr_assert(eq(dbl, m.mx[1][0], 5.5));
	cr_assert(eq(dbl, m.mx[1][1], 6.5));
	cr_assert(eq(dbl, m.mx[1][2], 7.5));
	cr_assert(eq(dbl, m.mx[1][3], 8.5));

	cr_assert(eq(dbl, m.mx[2][0], 9));
	cr_assert(eq(dbl, m.mx[2][1], 10));
	cr_assert(eq(dbl, m.mx[2][2], 11));
	cr_assert(eq(dbl, m.mx[2][3], 12));

	cr_assert(eq(dbl, m.mx[3][0], 13.5));
	cr_assert(eq(dbl, m.mx[3][1], 14.5));
	cr_assert(eq(dbl, m.mx[3][2], 15.5));
	cr_assert(eq(dbl, m.mx[3][3], 16.5));
}

Test(matrices, create_2x2_matrix)
{
	t_matrix	m;
	const double	table[MAX][MAX] = {
		{-3, 5},
		{1, -2},
	};

	m = new_matrix(table, 2);
	cr_assert(eq(dbl, m.mx[0][0], -3));
	cr_assert(eq(flt, m.mx[0][1], 5));
	cr_assert(eq(flt, m.mx[1][0], 1));
	cr_assert(eq(flt, m.mx[1][1], -2));
}

Test(matrices, create_matrix_3x3)
{
	t_matrix	m;

	const double	table[MAX][MAX] = {
		{-3, 5, 0},
		{1, -2, -7},
		{0, 1, 1},
	};

	m = new_matrix(table, 3);
	cr_assert(eq(dbl, m.mx[0][0], -3));
	cr_assert(eq(dbl, m.mx[0][1], 5));
	cr_assert(eq(dbl, m.mx[0][2], 0));

	cr_assert(eq(dbl, m.mx[1][0], 1));
	cr_assert(eq(dbl, m.mx[1][1], -2));
	cr_assert(eq(dbl, m.mx[1][2], -7));

	cr_assert(eq(dbl, m.mx[2][0], 0));
	cr_assert(eq(dbl, m.mx[2][1], 1));
	cr_assert(eq(dbl, m.mx[2][2], 1));
}

Test(matrices, is_equal_matrix)
{
	t_matrix	a;
	t_matrix	b;
	bool			result;
	const double	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};
	const double	table_b[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	a = new_matrix(table_a, MAX);
	b = new_matrix(table_b, MAX);
	result = is_eq_mx(a, b);
	cr_assert(eq(int, result, 1));
}

Test(matrices, is_not_equal_matrix)
{
	t_matrix	a;
	t_matrix	b;
	bool			result;
	const double	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{8, 7, 6, 5},
		{4, 3, 2, 1},
	};
	const double	table_b[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	a = new_matrix(table_a, MAX);
	b = new_matrix(table_b, MAX);
	result = is_eq_mx(a, b);
	cr_assert(ne(int, result, 1));
}

Test(matrices, multiply_matrices)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;

	const double	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	const double	table_b[MAX][MAX] = {
		{-2, 1, 2, 3},
		{3, 2, 1, -1},
		{4, 3, 6, 5},
		{1, 2, 7, 8},
	};

	a = new_matrix(table_a, MAX);
	b = new_matrix(table_b, MAX);
	c = multiply_matrices(a, b);

	cr_assert(eq(dbl, c.mx[0][0], 20));
	cr_assert(eq(dbl, c.mx[0][1], 22));
	cr_assert(eq(dbl, c.mx[0][2], 50));
	cr_assert(eq(dbl, c.mx[0][3], 48));

	cr_assert(eq(dbl, c.mx[1][0], 44));
	cr_assert(eq(dbl, c.mx[1][1], 54));
	cr_assert(eq(dbl, c.mx[1][2], 114));
	cr_assert(eq(dbl, c.mx[1][3], 108));

	cr_assert(eq(dbl, c.mx[2][0], 40));
	cr_assert(eq(dbl, c.mx[2][1], 58));
	cr_assert(eq(dbl, c.mx[2][2], 110));
	cr_assert(eq(dbl, c.mx[2][3], 102));

	cr_assert(eq(dbl, c.mx[3][0], 16));
	cr_assert(eq(dbl, c.mx[3][1], 26));
	cr_assert(eq(dbl, c.mx[3][2], 46));
	cr_assert(eq(dbl, c.mx[3][3], 42));
}

Test(matrices, multiply_mx_by_tuple)
{
	t_matrix	a;
	t_tuple		b;
	t_tuple		c;
	double const	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{2, 4, 4, 2},
		{8, 6, 4, 1},
		{0, 0, 0, 1},
	};

	a = new_matrix(table_a, MAX);
	b = new_tuple(1, 2, 3, 1);
	c = multiply_matrix_by_tuple(a, b);
	cr_assert(eq(dbl, c.x, 18));
	cr_assert(eq(dbl, c.y, 24));
	cr_assert(eq(dbl, c.z, 33));
	cr_assert(eq(dbl, c.w, 1));
}

Test(matrices, multiply_by_identity_matrix)
{
	t_matrix	a;
	t_matrix	id;
	t_matrix	result;
	double const	table_a[MAX][MAX] = {
		{0, 1, 2, 4},
		{1, 2, 4, 8},
		{2, 4, 8, 16},
		{4, 8, 16, 32},
	};
	double const table_id[MAX][MAX] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};

	a = new_matrix(table_a, MAX);
	id = new_matrix(table_id, MAX);
	result = multiply_matrices(a, id);

	cr_assert(eq(dbl, result.mx[0][0], 0));
	cr_assert(eq(dbl, result.mx[0][1], 1));
	cr_assert(eq(dbl, result.mx[0][2], 2));
	cr_assert(eq(dbl, result.mx[0][3], 4));

	cr_assert(eq(dbl, result.mx[1][0], 1));
	cr_assert(eq(dbl, result.mx[1][1], 2));
	cr_assert(eq(dbl, result.mx[1][2], 4));
	cr_assert(eq(dbl, result.mx[1][3], 8));

	cr_assert(eq(dbl, result.mx[2][0], 2));
	cr_assert(eq(dbl, result.mx[2][1], 4));
	cr_assert(eq(dbl, result.mx[2][2], 8));
	cr_assert(eq(dbl, result.mx[2][3], 16));

	cr_assert(eq(dbl, result.mx[3][0], 4));
	cr_assert(eq(dbl, result.mx[3][1], 8));
	cr_assert(eq(dbl, result.mx[3][2], 16));
	cr_assert(eq(dbl, result.mx[3][3], 32));
}

Test(matrices, transpose_matrix)
{
	t_matrix	a;
	t_matrix	result;
	double const	table_a[MAX][MAX] = {
		{0, 9, 3, 0},
		{9, 8, 0, 8},
		{1, 8, 5, 3},
		{0, 0, 5, 8},
	};

	a = new_matrix(table_a, MAX);
	result = transpose_matrix(a);

	cr_assert(eq(dbl, result.mx[0][0], 0));
	cr_assert(eq(dbl, result.mx[0][1], 9));
	cr_assert(eq(dbl, result.mx[0][2], 1));
	cr_assert(eq(dbl, result.mx[0][3], 0));

	cr_assert(eq(dbl, result.mx[1][0], 9));
	cr_assert(eq(dbl, result.mx[1][1], 8));
	cr_assert(eq(dbl, result.mx[1][2], 8));
	cr_assert(eq(dbl, result.mx[1][3], 0));

	cr_assert(eq(dbl, result.mx[2][0], 3));
	cr_assert(eq(dbl, result.mx[2][1], 0));
	cr_assert(eq(dbl, result.mx[2][2], 5));
	cr_assert(eq(dbl, result.mx[2][3], 5));

	cr_assert(eq(dbl, result.mx[3][0], 0));
	cr_assert(eq(dbl, result.mx[3][1], 8));
	cr_assert(eq(dbl, result.mx[3][2], 3));
	cr_assert(eq(dbl, result.mx[3][3], 8));
}

Test(matrices, determinant_2x2)
{
	t_matrix	a;
	int				result;
	double const	table_a[MAX][MAX] = {
		{1, 5},
		{-3, 2},
	};

	a = new_matrix(table_a, 2);
	result = get_determinant(a);
	cr_assert(eq(int, result, 17));
}

Test(matrices, submatrix_3x3)
{
	t_matrix	a;
	t_matrix	result;
	double const	table_a[MAX][MAX] = {
		{1, 5, 0},
		{-3, 2, 7},
		{0, 6, -3},
	};

	a = new_matrix(table_a, 3);
	result = get_submatrix(a, 0, 2);

	cr_assert(eq(dbl, result.mx[0][0], -3));
	cr_assert(eq(dbl, result.mx[0][1], 2));

	cr_assert(eq(dbl, result.mx[1][0], 0));
	cr_assert(eq(dbl, result.mx[1][1], 6));
}

Test(matrices, submatrix_4x4)
{
	t_matrix	a;
	t_matrix	result;
	double const	table_a[MAX][MAX] = {
		{-6, 1, 1, 6},
		{-8, 5, 8, 6},
		{-1, 0, 8, 2},
		{-7, 1, -1, 1},
	};

	a = new_matrix(table_a, 4);
	result = get_submatrix(a, 2, 1);

	cr_assert(eq(dbl, result.mx[0][0], -6));
	cr_assert(eq(dbl, result.mx[0][1], 1));
	cr_assert(eq(dbl, result.mx[0][2], 6));

	cr_assert(eq(dbl, result.mx[1][0], -8));
	cr_assert(eq(dbl, result.mx[1][1], 8));
	cr_assert(eq(dbl, result.mx[1][2], 6));

	cr_assert(eq(dbl, result.mx[2][0], -7));
	cr_assert(eq(dbl, result.mx[2][1], -1));
	cr_assert(eq(dbl, result.mx[2][2], 1));
}
