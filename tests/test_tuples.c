/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tuples.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:07:56 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/04/19 16:38:59 by johnavar         ###   ########.fr       */
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

Test(tuples, negating_a_tuple)
{
	t_vector result;

	result = negate(tuple(1, -2, 3, -4));
	cr_assert(eq(flt, result.x, -1));
	cr_assert(eq(flt, result.y, 2));
	cr_assert(eq(flt, result.z, -3));
	cr_assert(eq(flt, result.w, 4));
}

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

Test(tuples, dividing_a_tuple_by_a_scalar)
{
	t_tuple	result;

	result = division(tuple(1, -2, 3, -4), 2);
	cr_assert(eq(flt, result.x, 0.5));
	cr_assert(eq(flt, result.y, -1));
	cr_assert(eq(flt, result.z, 1.5));
	cr_assert(eq(flt, result.w, -2));
}

Test(tuples, computing_the_magnitude_of_a_vector)
{
	double result;

	result = magnitude(vector(1, 0, 0));
	cr_assert(eq(flt, result, 1));
	result = magnitude(vector(0, 1, 0));
	cr_assert(eq(flt, result, 1));
	result = magnitude(vector(0, 0, 1));
	cr_assert(eq(flt, result, 1));
	result = magnitude(vector(1, 2, 3));
	cr_assert(eq(flt, result, 3.7416573868));
	result = magnitude(vector(-1, -2, -3));
	cr_assert(eq(flt, result, 3.7416573868));
}
