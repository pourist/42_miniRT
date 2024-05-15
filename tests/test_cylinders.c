#include "test.h"

Test(cylinders, a_ray_misses_a_cylinder)
{
	t_shape		cyl;
	t_vector	dir;
	t_ray			r;
	t_hit			*xs;

	cyl = new_cylinder();
	xs = NULL;
	dir = normalize(new_vector(0, 1, 0));
	r = new_ray(new_point(1, 0, 0), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 0));
	dir = normalize(new_vector(0, 1, 0));
	r = new_ray(new_point(0, 0, 0), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 0));
	dir = normalize(new_vector(1, 1, 1));
	r = new_ray(new_point(0, 0, -5), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 0));
}

Test(cylinder, a_ray_strikes_a_cylinder)
{
  t_shape		cyl;
  t_vector	dir;
  t_ray			r;
  t_hit			*xs;

	cyl = new_cylinder();
	xs = NULL;
	dir = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(1, 0, -5), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 5, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 5, EPSILON));
	xs = NULL;
	dir = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(0, 0, -5), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 4, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 6, EPSILON));
	xs = NULL;
	dir = normalize(new_vector(0.1, 1, 1));
	r = new_ray(new_point(0.5, 0, -5), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 6.80798, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 7.08872, EPSILON));
}

Test(cylinder, normal_vector_on_a_cylinder)
{
	t_shape	cyl;
	t_vector	norm;

	cyl = new_cylinder();
	norm = cyl.normal_at(&cyl, new_point(1, 0, 0));
	cr_assert(eq(dbl, norm.x, 1));
	cr_assert(eq(dbl, norm.y, 0));
	cr_assert(eq(dbl, norm.z, 0));
	norm = cyl.normal_at(&cyl, new_point(0, 5, -1));
	cr_assert(eq(dbl, norm.x, 0));
	cr_assert(eq(dbl, norm.y, 0));
	cr_assert(eq(dbl, norm.z, -1));
	norm = cyl.normal_at(&cyl, new_point(0, -2, 1));
	cr_assert(eq(dbl, norm.x, 0));
	cr_assert(eq(dbl, norm.y, 0));
	cr_assert(eq(dbl, norm.z, 1));
	norm = cyl.normal_at(&cyl, new_point(-1, 1, 0));
	cr_assert(eq(dbl, norm.x, -1));
	cr_assert(eq(dbl, norm.y, 0));
	cr_assert(eq(dbl, norm.z, 0));
}

Test(cylinder, the_default_minimum_and_maximum_for_a_cylinder)
{
	t_shape	cyl;

	cyl = new_cylinder();
	cr_assert(eq(dbl, cyl.cyl.min, -INFINITY));
	cr_assert(eq(dbl, cyl.cyl.max, INFINITY));
}

Test(cylinder, intersecting_a_constrained_cylinder)
{
	t_shape	cyl;
	t_vector	dir;
	t_ray			r;
	t_hit			*xs;

	cyl = new_cylinder();
	cyl.cyl.min = 1;
	cyl.cyl.max = 2;
	xs = NULL;
	dir = normalize(new_vector(0.1, 1, 0));
	r = new_ray(new_point(0, 1.5, 0), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 0));
	dir = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(0, 3, -5), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 0));
	dir = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(0, 0, -5), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 0));
	dir = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(0, 2, -5), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 0));
	dir = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(0, 1, -5), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 0));
	dir = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(0, 1.5, -2), dir);
	intersect(&xs, &cyl, r);
	cr_assert(eq(int, intersect_count(xs), 2));
}
