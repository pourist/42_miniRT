#include "test.h"

Test(patterns, checker_pattern_in_2D)
{
	t_checker	checkers;
	t_pattern		*res;
	t_color		expected;
	double		uv[2];
	t_pattern black;
	t_pattern white;

	black = new_solid_pattern(BLACK);
	white = new_solid_pattern(WHITE);
	checkers = uv_checkers(2, 2, &black, &white);
	uv[0] = 0.0;
	uv[1] = 0.0;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	expected = BLACK;
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
	uv[0] = 0.5;
	uv[1] = 0.0;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	expected = WHITE;
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
	uv[0] = 0.0;
	uv[1] = 0.5;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	expected = WHITE;
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
	uv[0] = 0.5;
	uv[1] = 0.5;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	expected = BLACK;
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
	uv[0] = 1.0;
	uv[1] = 1.0;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	expected = BLACK;
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
}

Test(patterns, sphere_mapping_3D_point)
{
	t_point		p;
	double		uv[2];
	
	new_point(0, 0, -1, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(1, 0, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0, 0, 1, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.5));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(-1, 0, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0, 1, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.5));
	cr_assert(eq(dbl, uv[1], 1.0));
	new_point(0, -1, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.5));
	cr_assert(eq(dbl, uv[1], 0.0));
	new_point(sqrt(2)/2, sqrt(2)/2, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
}

Test(patterns, using_texture_map_pattern_with_spherical_map)
{
	t_pattern	pattern;
	t_color		res;
	t_point		p;

	new_pattern(&pattern);
	new_uv_checkers_pattern(new_solid_pattern(BLACK), new_solid_pattern(WHITE), &pattern);
	pattern.texture_map.uv_pattern = uv_checkers(16, 8, pattern.a, pattern.b);
	texture_map(&pattern, &pattern.texture_map.uv_pattern, spherical_map);
	new_point(0.4315, 0.4670, 0.7719, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, WHITE), true));
	new_point(-0.9654, 0.2552, -0.0534, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, BLACK), true));
	new_point(0.1039, 0.7090, 0.6975, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, WHITE), true));
	new_point(-0.4986, -0.7856, -0.3663, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, BLACK), true));
	new_point(-0.0317, -0.9395, 0.3411, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, BLACK), true));
	new_point(0.4809, -0.7721, 0.4154, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, BLACK), true));
	new_point(0.0285, -0.9612, -0.2745, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, BLACK), true));
	new_point(-0.5734, -0.2162, -0.7903, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, WHITE), true));
	new_point(0.7688, -0.1470, 0.6223, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, BLACK), true));
	new_point(-0.7652, 0.2175, 0.6060, &p);
	res = pattern.pattern_at(&pattern, &p);
	cr_assert(eq(int, color_eq(res, BLACK), true));
}

Test(patterns, using_planar_mapping_on_3D_point)
{
	t_point		p;
	double		uv[2];

	new_point(0.25, 0, 0.5, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0.25, 0, -0.25, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(0.25, 0.5, -0.25, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(1.25, 0, 0.5, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0.25, 0, -1.75, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.25));
	new_point(1, 0, -1, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.0));
	new_point(0, 0, 0, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.0));
}

Test(patterns, using_cylindrical_mapping_on_3D_point)
{
  t_point		p;
  double		uv[2];

	new_point(0, 0, -1, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.0));
	new_point(0, 0.5, -1, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0, 1, -1, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.0));
	new_point(0.70711, 0.5, -0.70711, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.125));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(1, 0.5, 0, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0.70711, 0.5, 0.70711, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.375));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0, -0.25, 1, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.5));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(-0.70711, 0.5, 0.70711, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.625));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(-1, 1.25, 0, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.25));
	new_point(-0.70711, 0.5, -0.70711, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.875));
	cr_assert(eq(dbl, uv[1], 0.5));
}
