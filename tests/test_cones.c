#include "test.h"

Test(cones, intersecting_a_cone_with_a_ray)
{
	t_shape		cone;
	t_vector	dir;
	t_ray			r;
	t_hit			*xs;

	xs = NULL;
	new_cone(&cone); 
	dir = normalize(new_vector(0, 0, 1));
	r = new_ray(new_point(0, 0, -5), dir);
	intersect(&xs, &cone, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 5, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 5, EPSILON));
	xs = NULL;
	dir = normalize(new_vector(1, 1, 1));
	r = new_ray(new_point(0, 0, -5), dir);
	intersect(&xs, &cone, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 8.66025404, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 8.66025404, EPSILON));
	xs = NULL;
	dir = normalize(new_vector(-0.5, -1, 1));
	r = new_ray(new_point(1, 1, -5), dir);
	intersect(&xs, &cone, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 4.55006, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 49.44994, EPSILON));
}

Test(cones, intersecting_a_cone_with_a_ray_parallel_to_one_of_its_halves)
{
  t_shape		cone;
  t_vector	dir;
  t_ray			r;
  t_hit			*xs;

	new_cone(&cone); 
	dir = normalize(new_vector(0, 1, 1));
	r = new_ray(new_point(0, 0, -1), dir);
	xs = NULL;
	intersect(&xs, &cone, r);
	cr_assert(eq(int, intersect_count(xs), 1));
	cr_assert(epsilon_eq(dbl, xs->t, 0.35355, EPSILON));
}

Test(cones, intersecting_a_cone_end_caps)
{
	t_shape		cone;
	t_vector	dir;
	t_ray			r;
	t_hit			*xs;

	new_cone(&cone); 
	cone.cyl.min = -0.5;
	cone.cyl.max = 0.5;
	cone.cyl.closed = true;
	dir = normalize(new_vector(0, 1, 0));
	r = new_ray(new_point(0, 0, -5), dir);
	xs = NULL;
	intersect(&xs, &cone, r);
	cr_assert(eq(int, intersect_count(xs), 0));
	xs = NULL;
	dir = normalize(new_vector(0, 1, 1));
	r = new_ray(new_point(0, 0, -0.25), dir);
	intersect(&xs, &cone, r);
	cr_assert(eq(int, intersect_count(xs), 2));
	xs = NULL;
	dir = normalize(new_vector(0, 1, 0));
	r = new_ray(new_point(0, 0, -0.25), dir);
	intersect(&xs, &cone, r);
	cr_assert(eq(int, intersect_count(xs), 4));
}

Test(cones, computing_the_normal_vector_on_a_cone)
{
	t_shape		cone;
	t_vector	norm;

	new_cone(&cone); 
	norm = cone.normal_at(&cone, new_point(0, 0, 0));
	cr_assert(eq(dbl, norm.x, 0));
	cr_assert(eq(dbl, norm.y, 0));
	cr_assert(eq(dbl, norm.z, 0));
	norm = cone.normal_at(&cone, new_point(1, 1, 1));
	cr_assert(eq(dbl, norm.x, 1));
	cr_assert(eq(dbl, norm.y, -sqrt(2)));
	cr_assert(eq(dbl, norm.z, 1));
	norm = cone.normal_at(&cone, new_point(-1, -1, 0));
	cr_assert(eq(dbl, norm.x, -1));
	cr_assert(eq(dbl, norm.y, 1));
	cr_assert(eq(dbl, norm.z, 0));
}
