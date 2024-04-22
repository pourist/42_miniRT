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
	b = new_matrix(table_b, MAX)
	result = is_equal_mx(a, b);
}
