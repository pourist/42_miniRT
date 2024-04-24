#include "test.h"

Test(transformations, mult_by_a_translation_matrix)
{
	t_matrix	transform;
	t_point		p;
	t_point		result;

	transform = translation(5, -3, 2);
	p = new_point(-3, 4, 5);
	result = multiply_matrix_by_tuple(transform, p);

	cr_assert(eq(dbl, result.x, 2));
	cr_assert(eq(dbl, result.y, 1));
	cr_assert(eq(dbl, result.z, 7));
}

Test(transformations, mult_by_inverse_translation)
{
	t_matrix	inverse;
	t_point		result;

	inverse = inverse_matrix(translation(5, -3, 2));
	result = multiply_matrix_by_tuple(inverse, new_point(-3, 4, 5));

	cr_assert(eq(dbl, result.x, -8));
	cr_assert(eq(dbl, result.y, 7));
	cr_assert(eq(dbl, result.z, 3));
}

Test(transformations, translation_doesnt_affect_vectors)
{
	t_matrix	transform; 
	t_vector	result;

	transform = translation(5, -3, 2);
	result = multiply_matrix_by_tuple(transform, new_vector(-3, 4, 5));

	cr_assert(eq(dbl, result.x, -3));
	cr_assert(eq(dbl, result.y, 4));
	cr_assert(eq(dbl, result.z, 5));
}

Test(transformations, scaling_matrix_applied_to_point)
{
	t_matrix	transform; 
	t_point		result;

	transform = scaling(2, 3, 4);
	result = multiply_matrix_by_tuple(transform, new_point(-4, 6, 8));

	cr_assert(eq(dbl, result.x, -8));
	cr_assert(eq(dbl, result.y, 18));
	cr_assert(eq(dbl, result.z, 32));
}

Test(transformations, scaling_matrix_applied_to_vector)
{
	t_matrix	transform; 
	t_vector	result;

	transform = scaling(2, 3, 4);
	result = multiply_matrix_by_tuple(transform, new_vector(-4, 6, 8));

	cr_assert(eq(dbl, result.x, -8));
	cr_assert(eq(dbl, result.y, 18));
	cr_assert(eq(dbl, result.z, 32));
}

Test(transformations, mult_inverse_of_scaling_matrix)
{
	t_matrix	inverse; 
	t_vector	result;

	inverse = inverse_matrix(scaling(2, 3, 4));
	result = multiply_matrix_by_tuple(inverse, new_vector(-4, 6, 8));

	cr_assert(eq(dbl, result.x, -2));
	cr_assert(eq(dbl, result.y, 2));
	cr_assert(eq(dbl, result.z, 2));
}

Test(transformations, reflection_is_scaling_by_negative_values)
{
	t_matrix	trans; 
	t_point	result;

	trans = scaling(-1, 1, 1);
	result = multiply_matrix_by_tuple(trans, new_point(2, 3, 4));

	cr_assert(eq(dbl, result.x, -2));
	cr_assert(eq(dbl, result.y, 3));
	cr_assert(eq(dbl, result.z, 4));
}

