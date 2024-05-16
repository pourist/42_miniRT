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
	cr_assert(eq(ptr, group.g->shape, &child));
	cr_assert(eq(ptr, group.g->left, NULL));
	cr_assert(eq(ptr, group.g->right, NULL));
	cr_assert(eq(ptr, child.parent, &group));
}

Test(groups, intersecting_a_ray_with_an_empty_group)
{
	t_shape	group;
	t_ray	ray;
	t_hit	*xs;

	xs = NULL;
	group = new_group();
	ray = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	intersect(&xs, &group, ray);
	cr_assert(eq(int, intersect_count(xs), 0));
}

Test(groups, intersecting_a_ray_with_a_nonempty_group)
{
	t_shape	group;
	t_shape	s1;
	t_shape	s2;
	t_shape	s3;
	t_ray	ray;
	t_hit	*xs;

	xs = NULL;
	group = new_group();
	s1 = new_sphere();
	s2 = new_sphere();
	s3 = new_sphere();
	set_transform(&s2, translation(0, 0, -3));
	set_transform(&s3, translation(5, 0, 0));
	add_child(&group, &s1);
	add_child(&group, &s2);
	add_child(&group, &s3);
	ray = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	intersect(&xs, &group, ray);
	cr_assert(eq(int, intersect_count(xs), 4));
	cr_assert(eq(ptr, xs->obj, &s2));
	cr_assert(eq(ptr, xs->next->obj, &s2));
	cr_assert(eq(ptr, xs->next->next->obj, &s1));
	cr_assert(eq(ptr, xs->next->next->next->obj, &s1));
}

Test(groups, intersecting_a_transformed_group)
{
	t_shape	group;
	t_shape	s1;
	t_ray	ray;
	t_hit	*xs;

	xs = NULL;
	group = new_group();
	set_transform(&group, scaling(2, 2, 2));
	s1 = new_sphere();
	set_transform(&s1, translation(5, 0, 0));
	add_child(&group, &s1);
	ray = new_ray(new_point(10, 0, -10), new_vector(0, 0, 1));
	intersect(&xs, &group, ray);
	cr_assert(eq(int, intersect_count(xs), 2));
}

Test(groups, converting_a_point_from_world_to_object_space)
{
	t_shape	g1;
	t_shape	g2;
	t_shape	s1;
	t_point	p;

	g1 = new_group();
	set_transform(&g1, rotation_y(cos(M_PI_2), sin(M_PI_2)));
	g2 = new_group();
	set_transform(&g2, scaling(2, 2, 2));
	add_child(&g1, &g2);
	s1 = new_sphere();
	set_transform(&s1, translation(5, 0, 0));
	add_child(&g2, &s1);
	p = world_to_object(&s1, new_point(-2, 0, -10));
	cr_assert(epsilon_eq(dbl, p.x, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, p.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, p.z, -1, EPSILON));
}
