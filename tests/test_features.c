#include "test.h"
/*
 * Previous sequence generator approach
Test(features, a_number_generator_returns_a_cyclic_sequence_of_numbers)
{
	t_sequencer	gen;

	gen = new_sequencer(3, 0.1, 0.5, 1.0);
	cr_assert(epsilon_eq(dbl, next(&gen), 0.1, EPSILON));
	cr_assert(epsilon_eq(dbl, next(&gen), 0.5, EPSILON));
	cr_assert(epsilon_eq(dbl, next(&gen), 1.0, EPSILON));
	cr_assert(epsilon_eq(dbl, next(&gen), 0.1, EPSILON));
} */
