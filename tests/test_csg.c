#include "test.h"

Test(csg, csg_is_created_with_an_operation_and_two_shapes)
{
	t_shape	left;
	t_shape	right;
	t_shape	csg;

	left = new_sphere();
	right = new_cube();
	new_csg(UNION, &left, &right, &csg);
	cr_assert(eq(int, csg.is_csg, true));
	cr_assert(eq(int, csg.csg.operation, UNION));
	cr_assert(eq(ptr, csg.csg.left, &left));
	cr_assert(eq(ptr, csg.csg.right, &right));
	cr_assert(eq(ptr, left.parent, &csg));
	cr_assert(eq(ptr, right.parent, &csg));
}

Test(csg, evaluating_the_rule_for_a_csg_operation)
{
	bool		result;

	result = intersect_allowed(UNION, true, true, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(UNION, true, true, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(UNION, true, false, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(UNION, true, false, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(UNION, false, true, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(UNION, false, true, false);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(UNION, false, false, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(UNION, false, false, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, true, true, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, true, true, false);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(INTERSECT, true, false, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, true, false, false);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(INTERSECT, false, true, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, false, true, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, false, false, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(INTERSECT, false, false, false);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(DIFFERENCE, true, true, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(DIFFERENCE, true, true, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(DIFFERENCE, true, false, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(DIFFERENCE, true, false, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(DIFFERENCE, false, true, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(DIFFERENCE, false, true, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(DIFFERENCE, false, false, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(DIFFERENCE, false, false, false);
  cr_assert(eq(int, result, false));
}

// Test(csg, filtering_a_list_of_intersections)
// {
// 	t_shape		s1;
// 	t_shape		s2;
// 	t_shape		csg;
// 	t_hit		*xs;
// 	t_hit		*i1;
// 	t_hit		*i2;

// 	s1 = new_sphere();
// 	s2 = new_cube();
// 	new_csg(UNION, &s1, &s2, &csg);
// 	t_ray	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
// 	xs = intersection(3, &s1, &s2, &csg);
// 	i1 = xs;
// 	cr_assert(eq(int, xs->count, 2));
// 	cr_assert(eq(dbl, xs->t, 4.0));
// 	cr_assert(eq(ptr, xs->obj, &s1));
// 	cr_assert(eq(dbl, xs->next->t, 6.5));
// 	cr_assert(eq(ptr, xs->next->obj, &s2));
// }
