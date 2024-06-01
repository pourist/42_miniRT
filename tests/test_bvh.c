#include "test.h"

Test(bounding_box, check_all_shapes)
{
	t_shape	s;
	t_shape	p;
	t_shape	c;
	t_shape	cyl;
	t_shape	cone;
	t_shape	tri;

	new_sphere(&s);
	s.bounds_of(&s);
	cr_assert(eq(dbl, s.bounds.min.x, -1));
	cr_assert(eq(dbl, s.bounds.min.y, -1));
	cr_assert(eq(dbl, s.bounds.min.z, -1));
	cr_assert(eq(dbl, s.bounds.max.x, 1));
	cr_assert(eq(dbl, s.bounds.max.y, 1));
	cr_assert(eq(dbl, s.bounds.max.z, 1));
	new_plane(&p);
	p.bounds_of(&p);
	cr_assert(eq(dbl, p.bounds.min.x, -INFINITY));
	cr_assert(eq(dbl, p.bounds.min.y, 0));
	cr_assert(eq(dbl, p.bounds.min.z, -INFINITY));
	cr_assert(eq(dbl, p.bounds.max.x, INFINITY));
	cr_assert(eq(dbl, p.bounds.max.y, 0));
	cr_assert(eq(dbl, p.bounds.max.z, INFINITY));
	new_cube(&c);
	c.bounds_of(&c);
	cr_assert(eq(dbl, c.bounds.min.x, -1));
	cr_assert(eq(dbl, c.bounds.min.y, -1));
	cr_assert(eq(dbl, c.bounds.min.z, -1));
	cr_assert(eq(dbl, c.bounds.max.x, 1));
	cr_assert(eq(dbl, c.bounds.max.y, 1));
	cr_assert(eq(dbl, c.bounds.max.z, 1));
	new_cylinder(&cyl);
	cyl.cyl.min = -5;
	cyl.cyl.max = 3;
	cyl.bounds_of(&cyl);
	cr_assert(eq(dbl, cyl.bounds.min.x, -1));
	cr_assert(eq(dbl, cyl.bounds.min.y, -5));
	cr_assert(eq(dbl, cyl.bounds.min.z, -1));
	cr_assert(eq(dbl, cyl.bounds.max.x, 1));
	cr_assert(eq(dbl, cyl.bounds.max.y, 3));
	cr_assert(eq(dbl, cyl.bounds.max.z, 1));
	new_cone(&cone);
	cone.cone.min = -5;
	cone.cone.max = 3;
	cone.bounds_of(&cone);
	cr_assert(eq(dbl, cone.bounds.min.x, -5));
	cr_assert(eq(dbl, cone.bounds.min.y, -5));
	cr_assert(eq(dbl, cone.bounds.min.z, -5));
	cr_assert(eq(dbl, cone.bounds.max.x, 5));
	cr_assert(eq(dbl, cone.bounds.max.y, 3));
	cr_assert(eq(dbl, cone.bounds.max.z, 5));
	new_triangle(new_point(-3, 7, 2), new_point(6, 2, -4), new_point(2, -1, -1), &tri);
	tri.bounds_of(&tri);
	cr_assert(eq(dbl, tri.bounds.min.x, -3));
  cr_assert(eq(dbl, tri.bounds.min.y, -1));
  cr_assert(eq(dbl, tri.bounds.min.z, -4));
  cr_assert(eq(dbl, tri.bounds.max.x, 6));
  cr_assert(eq(dbl, tri.bounds.max.y, 7));
  cr_assert(eq(dbl, tri.bounds.max.z, 2));
}

Test(bounds, adding_one_bounding_box_to_another)
{
	t_shape	g;
	t_shape	s1;
	t_shape s2;

	new_group(&g);
	new_sphere(&s1);
	new_sphere(&s2);
	s1.bounds_of(&s1);
	s2.bounds_of(&s2);
	s1.bounds.min = new_point(-5, -2, 0);
	s1.bounds.max = new_point(7, 4, 4);
	s2.bounds.min = new_point(8, -7, -2);
	s2.bounds.max = new_point(14, 2, 8);
	add_child(&g, &s1);
	add_child(&g, &s2);
	g.bounds_of(&g);
	cr_assert(eq(dbl, g.bounds.min.x, -5));
	cr_assert(eq(dbl, g.bounds.min.y, -7));
	cr_assert(eq(dbl, g.bounds.min.z, -2));
	cr_assert(eq(dbl, g.bounds.max.x, 14));
	cr_assert(eq(dbl, g.bounds.max.y, 4));
	cr_assert(eq(dbl, g.bounds.max.z, 8));
}

Test(bounds, checking_to_see_if_a_box_contains_a_given_point)
{
	t_bounds b;
	t_point	p;

	b = new_bounds(new_point(5, -2, 0), new_point(11, 4, 7));
	p = new_point(5, -2, 0);
	cr_assert(eq(int, box_contains_point(&b, &p), true));
	p = new_point(11, 4, 7);
	cr_assert(eq(int, box_contains_point(&b, &p), true));
	p = new_point(8, 1, 3);
	cr_assert(eq(int, box_contains_point(&b, &p), true));
	p = new_point(3, 0, 3);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	p = new_point(8, -4, 3);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	p = new_point(8, 1, -1);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	p = new_point(13, 1, 3);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	p = new_point(8, 5, 3);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	p = new_point(8, 1, 8);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
}

Test(bounds, checking_to_see_if_a_box_contains_a_given_box)
{
	t_bounds b1;
	t_bounds b2;

	b1 = new_bounds(new_point(5, -2, 0), new_point(11, 4, 7));
	b2 = new_bounds(new_point(5, -2, 0), new_point(11, 4, 7));
	cr_assert(eq(int, box_contains_box(&b1, &b2), true));
	b2 = new_bounds(new_point(6, -1, 1), new_point(10, 3, 6));
	cr_assert(eq(int, box_contains_box(&b1, &b2), true));
	b2 = new_bounds(new_point(4, -3, -1), new_point(10, 3, 6));
	cr_assert(eq(int, box_contains_box(&b1, &b2), false));
	b2 = new_bounds(new_point(6, -1, 1), new_point(12, 5, 8));
	cr_assert(eq(int, box_contains_box(&b1, &b2), false));
}

Test(bounds, a_group_has_a_bounding_box_that_contains_its_children)
{
	t_shape	g;
	t_shape	s;
	t_shape	c;
	t_matrix m;

	new_group(&g);
	new_sphere(&s);
	new_cylinder(&c);
	c.cyl.min = -2;
	c.cyl.max = 2;
	m = multiply_matrices(translation(2, 5, -3), scaling(2, 2, 2));
	set_transform(&s, m);
	m = multiply_matrices(translation(-4, -1, 4), scaling(0.5, 1, 0.5));
	set_transform(&c, m);
	add_child(&g, &s);
	add_child(&g, &c);
	g.bounds_of(&g);
	cr_assert(eq(dbl, g.bounds.min.x, -4.5));
	cr_assert(eq(dbl, g.bounds.min.y, -3));
	cr_assert(eq(dbl, g.bounds.min.z, -5));
	cr_assert(eq(dbl, g.bounds.max.x, 4));
	cr_assert(eq(dbl, g.bounds.max.y, 7));
	cr_assert(eq(dbl, g.bounds.max.z, 4.5));
}

Test(bounds, a_csg_shape_has_a_bounding_box_that_contains_its_children)
{
	t_shape	csg;
	t_shape	s1;
	t_shape	s2;

	new_sphere(&s1);
	new_sphere(&s2);
	set_transform(&s2, translation(2, 3, 4));
	new_csg(DIFFERENCE, &s1, &s2, &csg);
	csg.bounds_of(&csg);
	cr_assert(eq(dbl, csg.bounds.min.x, -1));
	cr_assert(eq(dbl, csg.bounds.min.y, -1));
	cr_assert(eq(dbl, csg.bounds.min.z, -1));
	cr_assert(eq(dbl, csg.bounds.max.x, 3));
	cr_assert(eq(dbl, csg.bounds.max.y, 4));
	cr_assert(eq(dbl, csg.bounds.max.z, 5));
}

Test(bounds, intersecting_a_ray_with_a_bounding_box_at_the_origin)
{
	t_bounds b;
	t_ray	r;
	t_vector	d;

	b = new_bounds(new_point(-1, -1, -1), new_point(1, 1, 1));
	d = normalize(new_vector(-1, 0, 0));
	r = new_ray(new_point(5, 0.5, 0), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	d = normalize(new_vector(1, 0, 0));
	r = new_ray(new_point(-5, 0.5, 0), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	d = normalize(new_vector(0, -1, 0));
	r = new_ray(new_point(0.5, 5, 0), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	d = normalize(new_vector(0, 1, 0));
	r = new_ray(new_point(0.5, -5, 0), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	d = normalize(new_vector(0, 0, -1));
	r = new_ray(new_point(0.5, 0, 5), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	d = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(0.5, 0, -5), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	d = normalize(new_vector(2, 4, 6));
	r = new_ray(new_point(-2, 0, 0), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	d = normalize(new_vector(6, 2, 4));
	r = new_ray(new_point(0, -2, 0), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	d = normalize(new_vector(4, 6, 2));
	r = new_ray(new_point(0, 0, -2), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	d = normalize(new_vector(0, 0, -1));
	r = new_ray(new_point(2, 0, 2), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	d = normalize(new_vector(0, -1, 0));
	r = new_ray(new_point(0, 2, 2), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	d = normalize(new_vector(-1, 0, 0));
	r = new_ray(new_point(2, 2, 0), d);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
}

Test(bounds, intersecting_a_ray_with_a_non_cubic_bounding_box)
{
	t_bounds b;
	t_ray	r;

	b = new_bounds(new_point(5, -2, 0), new_point(11, 4, 7));
	r = new_ray(new_point(15, 1, 2), normalize(new_vector(-1, 0, 0)));
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	r = new_ray(new_point(-5, -1, 4), normalize(new_vector(1, 0, 0)));
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	r = new_ray(new_point(7, 6, 5), normalize(new_vector(0, -1, 0)));
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	r = new_ray(new_point(9, -5, 6), normalize(new_vector(0, 1, 0)));
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	r = new_ray(new_point(8, 2, 12), normalize(new_vector(0, 0, -1)));
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	r = new_ray(new_point(6, 0, -5), normalize(new_vector(0, 0, 1)));
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	r = new_ray(new_point(8, 1, 3.5), normalize(new_vector(0, 0, 1)));
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	r = new_ray(new_point(9, -1, -8), normalize(new_vector(2, 4, 6)));
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	r = new_ray(new_point(8, 3, -4), normalize(new_vector(6, 2, 4)));
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	r = new_ray(new_point(9, -1, -2), normalize(new_vector(4, 6, 2)));
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	r = new_ray(new_point(4, 0, 9), normalize(new_vector(0, 0, -1)));
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	r = new_ray(new_point(8, 6, -1), normalize(new_vector(0, -1, 0)));
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	r = new_ray(new_point(12, 5, 4), normalize(new_vector(-1, 0, 0)));
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
}
