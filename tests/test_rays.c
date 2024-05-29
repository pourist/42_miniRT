#include "test.h"

Test(rays, create_and_query_ray)
{
	t_ray	r;

	r = new_ray(new_point(1, 2, 3), new_vector(4, 5, 6));
	cr_assert(eq(dbl, r.origin.x, 1));
	cr_assert(eq(dbl, r.origin.y, 2));
	cr_assert(eq(dbl, r.origin.z, 3));
	cr_assert(eq(dbl, r.direction.x, 4));
	cr_assert(eq(dbl, r.direction.y, 5));
	cr_assert(eq(dbl, r.direction.z, 6));
}

Test(rays, computing_point_from_distance)
{
	t_ray		r;
	t_point	p;

	r = new_ray(new_point(2, 3, 4), new_vector(1, 0, 0));
	p = position(&r, 0);
	cr_assert(eq(dbl, p.x, 2));
	cr_assert(eq(dbl, p.y, 3));
	cr_assert(eq(dbl, p.z, 4));
	p = position(&r, 1);
	cr_assert(eq(dbl, p.x, 3));
	cr_assert(eq(dbl, p.y, 3));
	cr_assert(eq(dbl, p.z, 4));
	p = position(&r, -1);
	cr_assert(eq(dbl, p.x, 1));
	cr_assert(eq(dbl, p.y, 3));
	cr_assert(eq(dbl, p.z, 4));
	p = position(&r, 2.5);
	cr_assert(eq(dbl, p.x, 4.5));
	cr_assert(eq(dbl, p.y, 3));
	cr_assert(eq(dbl, p.z, 4));
}

Test(rays, translating_a_ray)
{
	t_ray			r1;
	t_ray			r2;
	t_matrix	m;
	
	r1 = new_ray(new_point(1, 2, 3), new_vector(0, 1, 0));
	m = translation(3, 4, 5);
	r2 = transform(&r1, &m);
	cr_assert(eq(dbl, r2.origin.x, 4));
	cr_assert(eq(dbl, r2.origin.y, 6));
	cr_assert(eq(dbl, r2.origin.z, 8));
	cr_assert(eq(dbl, r2.direction.x, 0));
	cr_assert(eq(dbl, r2.direction.y, 1));
	cr_assert(eq(dbl, r2.direction.z, 0));
}

Test(rays, scaling_a_ray)
{
	t_ray			r1;
	t_ray			r2;
	t_matrix	m;
	
	r1 = new_ray(new_point(1, 2, 3), new_vector(0, 1, 0));
	m = scaling(2, 3, 4);
	r2 = transform(&r1, &m);
	cr_assert(eq(dbl, r2.origin.x, 2));
	cr_assert(eq(dbl, r2.origin.y, 6));
	cr_assert(eq(dbl, r2.origin.z, 12));
	cr_assert(eq(dbl, r2.direction.x, 0));
	cr_assert(eq(dbl, r2.direction.y, 3));
	cr_assert(eq(dbl, r2.direction.z, 0));
}
