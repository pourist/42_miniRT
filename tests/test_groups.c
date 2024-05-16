#include "test.h"

Test(groups, creating_a_new_group)
{
	t_shape	shape;

	shape = new_group();
	cr_assert(eq(int, shape.g == NULL, 1));
	cr_assert(eq(int, matrix_eq(shape.transform, get_identity_matrix()), 1));
}

Test(groups, a_shape_has_a_parent_attribute)
{
	t_shape	shape;

	shape = new_shape();
	cr_assert(eq(ptr, shape.parent, NULL));
}

Test(groups, adding_a_child_to_group)
{
	t_shape	group;
	t_shape	child;

	group = new_group();
	child = new_shape();
	add_child(&group, &child);
	cr_assert(eq(ptr, group.g.shape, &child));
	cr_assert(eq(ptr, group.g.left, NULL));
	cr_assert(eq(ptr, group.g.right, NULL));
	cr_assert(eq(ptr, child.g.parent, &group));
	}
}
