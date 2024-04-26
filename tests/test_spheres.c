#include "test.h"

Test(spheres, a_ray_intersects_a_sphere_at_two_points)
{
	t_ray					r;
	t_shape				s;
	t_intersect		xs;

	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, xs.count, 2));
	cr_assert(eq(dbl, xs.t[0], 4.0));
	cr_assert(eq(dbl, xs.t[1], 6.0));
}

Test(spheres, a_ray_intersects_a_sphere_at_a_tangent)
{
	t_ray					r;
	t_shape				s;
	t_intersect		xs;

	r = new_ray(new_point(0, 1, -5), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, xs.count, 2));
	cr_assert(eq(dbl, xs.t[0], 5.0));
	cr_assert(eq(dbl, xs.t[1], 5.0));
}

Test(spheres, a_ray_misses_a_sphere)
{
	t_ray					r;
	t_shape				s;
	t_intersect		xs;

	r = new_ray(new_point(0, 2, -5), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, xs.count, 0));
}

Test(spheres, a_ray_originates_inside_a_sphere)
{
	t_ray					r;
	t_shape				s;
	t_intersect		xs;

	r = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, xs.count, 2));
	cr_assert(eq(dbl, xs.t[0], -1.0));
	cr_assert(eq(dbl, xs.t[1], 1.0));
}

Test(spheres, a_sphere_is_behind_a_ray)
{
	t_ray					r;
	t_shape				s;
	t_intersect		xs;

	r = new_ray(new_point(0, 0, 5), new_vector(0, 0, 1));
	s = new_sphere();
	intersect(&xs, &s, r);
	cr_assert(eq(int, xs.count, 2));
	cr_assert(eq(dbl, xs.t[0], -6.0));
	cr_assert(eq(dbl, xs.t[1], -4.0));
}
