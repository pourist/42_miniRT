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
	p = position(r, 0);
	cr_assert(eq(dbl, p.x, 2));
	cr_assert(eq(dbl, p.y, 3));
	cr_assert(eq(dbl, p.z, 4));
	p = position(r, 1);
	cr_assert(eq(dbl, p.x, 3));
	cr_assert(eq(dbl, p.y, 3));
	cr_assert(eq(dbl, p.z, 4));
	p = position(r, -1);
	cr_assert(eq(dbl, p.x, 1));
	cr_assert(eq(dbl, p.y, 3));
	cr_assert(eq(dbl, p.z, 4));
	p = position(r, 2.5);
	cr_assert(eq(dbl, p.x, 4.5));
	cr_assert(eq(dbl, p.y, 3));
	cr_assert(eq(dbl, p.z, 4));
}
