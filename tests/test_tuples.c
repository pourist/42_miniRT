/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tuples.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:07:56 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/04/20 17:25:01 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
Test if the function tuple create correctly a tuple with the given arguments.
*/
Test(tuples, create_a_tuple)
{
	t_tuple a;

	a = tuple(4.2, -4.2, 3.2, 1.0);
	cr_assert(eq(flt, a.x, 4.2));
	cr_assert(eq(flt, a.y, -4.2));
	cr_assert(eq(flt, a.z, 3.2));
	cr_assert(eq(flt, a.w, 1.0));
}

/*
Test if the function point create correctly a tuple with the given arguments
w is set to 1.0 by default.
*/
Test(tuples, create_a_point)
{
	t_tuple a;

	a = point(4.2, -4.2, 3.2);
	cr_assert(eq(flt, a.x, 4.2));
	cr_assert(eq(flt, a.y, -4.2));
	cr_assert(eq(flt, a.z, 3.2));
	cr_assert(eq(flt, a.w, 1.0));
}

/*
Test if the function vector create correctly a tuple with the given arguments
w is set to 0.0 by befault.
*/
Test(tuples, create_a_vector)
{
	t_tuple a;

	a = vector(4.2, -4.2, 3.2);
	cr_assert(eq(flt, a.x, 4.2));
	cr_assert(eq(flt, a.y, -4.2));
	cr_assert(eq(flt, a.z, 3.2));
	cr_assert(eq(flt, a.w, 0.0));
}

/* Test if the function "add", adds two tuples correctly. */
Test(tuples, adding_a_tuples)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple result;

	a = tuple(3, -2, 5, 1.0);
	b = tuple(-2, 3, 1, 0.0);
	result = add(a, b);
	cr_assert(eq(flt, result.x, 1));
	cr_assert(eq(flt, result.y, 1));
	cr_assert(eq(flt, result.z, 6));
	cr_assert(eq(flt, result.w, 1));
}

Test(tuples, adding_a_tuples_2)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple result;

	a = tuple(6, 5, 4, 1.0);
	b = tuple(-2, 6, 4, 0.0);
	result = add(a, b);
	cr_assert(eq(flt, result.x, 4));
	cr_assert(eq(flt, result.y, 11));
	cr_assert(eq(flt, result.z, 8));
	cr_assert(eq(flt, result.w, 1));
}

/* test if the function "subtract", subtracts two tuples correctly. */
Test(tuples, subtracting_a_tuples)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple result;

	a = point(3, 2, 1);
	b = point(5, 6, 7);
	result = subtract(a, b);
	cr_assert(eq(flt, result.x, -2));
	cr_assert(eq(flt, result.y, -4));
	cr_assert(eq(flt, result.z, -6));
	cr_assert(eq(flt, result.w, 0));
	a = point(3, 2, 1);
	b = vector(5, 6, 7);
	cr_assert(eq(flt, result.x, -2));
	cr_assert(eq(flt, result.y, -4));
	cr_assert(eq(flt, result.z, -6));
	cr_assert(eq(flt, result.w, -0));
	a = vector(3, 2, 1);
	b = vector(5, 6, 7);
	cr_assert(eq(flt, result.x, -2));
	cr_assert(eq(flt, result.y, -4));
	cr_assert(eq(flt, result.z, -6));
	cr_assert(eq(flt, result.w, 0));
}

/* Test if the function "negate", negates a tuple correctly. */
Test(tuples, negating_a_tuple)
{
	t_vector result;

	result = negate(tuple(1, -2, 3, -4));
	cr_assert(eq(flt, result.x, -1));
	cr_assert(eq(flt, result.y, 2));
	cr_assert(eq(flt, result.z, -3));
	cr_assert(eq(flt, result.w, 4));
}

/* Test if the function "multiply", multiplies a tuple by a scalar correctly. */
Test(tuples, multiplying_a_tuple_by_a_scalar)
{
	t_tuple	result;

	result = multiply(tuple(1, -2, 3, -4), 3.5);
	cr_assert(eq(flt, result.x, 3.5));
	cr_assert(eq(flt, result.y, -7));
	cr_assert(eq(flt, result.z, 10.5));
	cr_assert(eq(flt, result.w, -14));
	result = multiply(tuple(1, -2, 3, -4), 0.5);
	cr_assert(eq(flt, result.x, 0.5));
	cr_assert(eq(flt, result.y, -1));
	cr_assert(eq(flt, result.z, 1.5));
	cr_assert(eq(flt, result.w, -2));
}

/* test if the function "divide", divides a tuple by a scalar correctly. */
Test(tuples, dividing_a_tuple_by_a_scalar)
{
	t_tuple	result;

	result = division(tuple(1, -2, 3, -4), 2);
	cr_assert(eq(flt, result.x, 0.5));
	cr_assert(eq(flt, result.y, -1));
	cr_assert(eq(flt, result.z, 1.5));
	cr_assert(eq(flt, result.w, -2));
}

/* Test if the function "magnitude", computes the magnitude of a vector correctly. */
Test(tuples, computing_the_magnitude_of_a_vector)
{
	double length;

	length = magnitude(vector(1, 0, 0));
	cr_assert(eq(flt, length, 1));
	length = magnitude(vector(0, 1, 0));
	cr_assert(eq(flt, length, 1));
	length = magnitude(vector(0, 0, 1));
	cr_assert(eq(flt, length, 1));
	length = magnitude(vector(1, 2, 3));
	cr_assert(eq(flt, length, 3.7416573868));
	length = magnitude(vector(-1, -2, -3));
	cr_assert(eq(flt, length, 3.7416573868));
}

/* Test if the function "normalize" correctly normalizes a vector. */
Test(tuples, normalizing_vectors)
{
	t_tuple	v;
	t_tuple	normal;

	v = vector(4, 0, 0);
	normal = normalize(v);
	cr_assert(epsilon_eq(flt, magnitude(normal), 1, DBL_EPSILON));

	v = vector(1, 2, 3);
	normal = normalize(v);
	cr_assert(epsilon_eq(flt, magnitude(normal), 1, DBL_EPSILON));
}

/* Test if the function "dot" computes the dot product of two vectors correctly. */
Test(tuples, dot_product_of_two_vectors)
{
	t_vector	a;
	t_vector	b;
	double		result;

	a = vector(1, 2, 3);
	b = vector(2, 3, 4);
	result = dot(a, b);
	cr_assert(eq(flt, result, 20));
}

Test(tuples, cross_product_of_two_vectors)
{
	t_vector	a;
	t_vector	b;
	t_vector	result;
	a = vector(1, 2, 3);
	b = vector(2, 3, 4);
	result = cross(a, b);
	cr_assert(eq(flt, result.x, -1));
	cr_assert(eq(flt, result.y, 2));
	cr_assert(eq(flt, result.z, -1));
	result = cross(b, a);
	cr_assert(eq(flt, result.x, 1));
	cr_assert(eq(flt, result.y, -2));
	cr_assert(eq(flt, result.z, 1));
}
