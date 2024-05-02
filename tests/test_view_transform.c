#include "test.h"

Test(view_transformations, transformation_matrix_for_the_default_orientation)
{
	t_point from;
	t_point to;
	t_vector up;
	t_matrix t;

	from = new_point(0, 0, 0);
	to = new_point(0, 0, -1);
	up = new_vector(0, 1, 0);
	t = view_transform(&from, &to, &up);
	cr_assert(matrix_eq(t, get_identity_matrix()));
}

Test(view_transformations, view_transformation_matrix_looking_in_positive_z_direction)
{
	t_point from;
	t_point to;
	t_vector up;
	t_matrix t;

	from = new_point(0, 0, 0);
	to = new_point(0, 0, 1);
	up = new_vector(0, 1, 0);
	t = view_transform(&from, &to, &up);
	cr_assert(matrix_eq(t, scaling(-1, 1, -1)));
}

Test(view_transformations, view_transformation_moves_the_world)
{
	t_point from;
	t_point to;
	t_vector up;
	t_matrix t;

	from = new_point(0, 0, 8);
	to = new_point(0, 0, 0);
	up = new_vector(0, 1, 0);
	t = view_transform(&from, &to, &up);
	cr_assert(matrix_eq(t, translation(0, 0, -8)));
}

Test(view_transformations, arbitrary_view_transformation)
{
	t_point from;
	t_point to;
	t_vector up;
	t_matrix t;
	const double	expected[MAX][MAX] = {
		{-0.50709, 0.50709,  0.67612, -2.36643},
		{ 0.76772, 0.60609,  0.12122, -2.82843},
		{-0.35857, 0.59761, -0.71714,  0.00000},
		{ 0.00000, 0.00000,  0.00000,  1.00000},
	};

	from = new_point(1, 3, 2);
	to = new_point(4, -2, 8);
	up = new_vector(1, 1, 0);
	t = view_transform(&from, &to, &up);
	cr_assert(matrix_eq(t, new_matrix(expected, 4)));
}
