#include "test.h"

Test(spheres, a_ray_intersects_a_sphere_at_two_points)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;

	xs = NULL;
	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(dbl, xs->next->t, 6));
}

Test(spheres, a_ray_intersects_a_sphere_at_a_tangent)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;

	xs = NULL;
	r = new_ray(new_point(0, 1, -5), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 5.0));
	cr_assert(eq(dbl, xs->next->t, 5.0));
}

Test(spheres, a_ray_misses_a_sphere)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;

	xs = NULL;
	r = new_ray(new_point(0, 2, -5), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, intersect_count(xs), 0));
}

Test(spheres, a_ray_originates_inside_a_sphere)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;

	xs = NULL;
	r = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, -1.0));
	cr_assert(eq(dbl, xs->next->t, 1.0));
}

Test(spheres, a_sphere_is_behind_a_ray)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;

	xs = NULL;
	r = new_ray(new_point(0, 0, 5), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, -6.0));
	cr_assert(eq(dbl, xs->next->t, -4.0));
}

Test(spheres, an_intersection_encapsulates_t_and_object)
{
	t_shape				s;
	t_hit					*xs;

	s = new_sphere();
	xs = intersection(3.5, &s);
	cr_assert(eq(int, intersect_count(xs), 1));
	cr_assert(eq(dbl, xs->t, 3.5));
	cr_assert(xs->obj == &s);
}

Test(intersections, aggregating_intersections)
{
	t_shape	s;
	t_hit		*i1;
	t_hit		*i2;
	t_hit		*xs;

	xs = NULL;
	s = new_sphere();
	i1 = intersection(1, &s);
	i2 = intersection(2, &s);
	insert_intersection(&xs, i1);
	insert_intersection(&xs, i2);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 1));
	cr_assert(eq(dbl, xs->next->t, 2));
}

Test(intersections, intersect_sets_object_on_intersection)
{
	t_shape	s;
	t_ray		r;
	t_hit		*xs;

	xs = NULL;
	s = new_sphere();
	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	intersect(&xs, &s, r);
	cr_assert(xs->obj == &s);
	cr_assert(xs->next->obj == &s);
}
