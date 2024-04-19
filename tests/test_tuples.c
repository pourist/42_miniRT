/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tuples.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:07:56 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/04/19 09:57:01 by sebasnadu        ###   ########.fr       */
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

Test(tuples, adding_tuples)
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
