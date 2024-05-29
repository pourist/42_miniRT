#include "test.h"

/* Test if a newly created shape has a default transformation
 * matrix set to the identity matrix. */
Test(shapes, the_default_transformation)
{
	t_shape	s;

	new_shape(&s);
	cr_assert(matrix_eq(s.transform, get_identity_matrix()));
}

/* Test if the transformation matrix of a shape can be successfully changed. */
Test(shapes, assigning_a_transformation)
{
	t_shape		s;
	t_matrix	expected;

	new_shape(&s);
	expected = translation(2, 3, 3);
	set_transform(&s, expected);
	cr_assert(matrix_eq(s.transform, expected));
}

/* Test that when a shape is created, it has a default material assigned to it. */
Test(shapes, the_default_material)
{
	t_shape		s;
	t_material	result;
	t_material	expected;

	new_shape(&s);
	result = s.material;
	expected = new_material();

	cr_assert(epsilon_eq(result.color.r, expected.color.r, EPSILON));
	cr_assert(epsilon_eq(result.color.g, expected.color.g, EPSILON));
	cr_assert(epsilon_eq(result.color.b, expected.color.b, EPSILON));
	cr_assert(epsilon_eq(result.ambient.r, expected.ambient.r, EPSILON));
	cr_assert(epsilon_eq(result.ambient.g, expected.ambient.g, EPSILON));
	cr_assert(epsilon_eq(result.ambient.b, expected.ambient.b, EPSILON));
	cr_assert(epsilon_eq(result.diffuse, expected.diffuse, EPSILON));
	cr_assert(epsilon_eq(result.specular, expected.specular, EPSILON));
	cr_assert(epsilon_eq(result.shininess, expected.shininess, EPSILON));
}

/* Test if a material can be successfully assigned to a shape. */
Test(shapes, assigning_a_material)
{
	t_shape		s;
	t_material	expected;

	new_shape(&s);
	expected = new_material();
	expected.ambient = new_color(1, 1, 1);
	s.material = expected;

	cr_assert(epsilon_eq(s.material.color.r, expected.color.r, EPSILON));
	cr_assert(epsilon_eq(s.material.color.g, expected.color.g, EPSILON));
	cr_assert(epsilon_eq(s.material.color.b, expected.color.b, EPSILON));
	cr_assert(epsilon_eq(s.material.ambient.r, expected.ambient.r, EPSILON));
	cr_assert(epsilon_eq(s.material.ambient.g, expected.ambient.g, EPSILON));
	cr_assert(epsilon_eq(s.material.ambient.b, expected.ambient.b, EPSILON));
	cr_assert(epsilon_eq(s.material.diffuse, expected.diffuse, EPSILON));
	cr_assert(epsilon_eq(s.material.specular, expected.specular, EPSILON));
	cr_assert(epsilon_eq(s.material.shininess, expected.shininess, EPSILON));
}

/* Tests the ability to compute the normal of a geometric shape that has been
 * translated to a specific position. */
Test(shapes, normal_on_a_translated_shape)
{
	t_shape		s;
	t_vector	n;
	t_point		p;

	new_sphere(&s);
	set_transform(&s, translation(0, 1, 0));
	p = new_point(0, 1.70711, -0.70711);
	n = normal_at(&s, &p);

	cr_assert(epsilon_eq(n.x, 0, EPSILON));
	cr_assert(epsilon_eq(n.y, 0.70711, EPSILON));
	cr_assert(epsilon_eq(n.z, -0.70711, EPSILON));
}

/* Tests the ability to compute the normal of a geometric shape that has been
 * transformed through a sequence of transformations. */
Test(shapes, normal_on_a_transformed_shape)
{
	t_shape		s;
	t_matrix	m;
	t_vector	n;
	t_point		p;

	new_sphere(&s);
	m = multiply_matrices(scaling(1, 0.5, 1), rotation_z(cos(M_PI/5), sin(M_PI/5)));
	set_transform(&s, m);
	p = new_point(0, sqrtf(2)/2, -sqrtf(2)/2);
	n = normal_at(&s, &p);

	cr_assert(epsilon_eq(n.x, 0, EPSILON));
	cr_assert(epsilon_eq(n.y, 0.97014, EPSILON));
	cr_assert(epsilon_eq(n.z, -0.24254, EPSILON));
}
