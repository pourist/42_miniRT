#include "test.c"

Test(patterns, create_stripe_feature)
{
	t_pattern	pattern;
	t_color		white;
	t_color		black;
	
	pattern.a = WHITE;
	pattern.b = BLACK;
	white = new_color(1, 1, 1);
	black = new_color(0, 0, 0);

	cr_assert(eq(dbl, pattern.a.r, white.r));
	cr_assert(eq(dbl, pattern.a.g, white.g));
	cr_assert(eq(dbl, pattern.a.b, white.b));

	cr_assert(eq(dbl, pattern.b.r, black.r));
	cr_assert(eq(dbl, pattern.b.g, black.g));
	cr_assert(eq(dbl, pattern.b.b, black.b));
}

Test(patterns, new_pattern_constant_in_y_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_y_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 1, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_y_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 2, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

/* A stripe pattern is constant in z */
Test(patterns, new_pattern_constant_in_z_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_z_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 1);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_z_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 2);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

/* A stripe pattern is constant in x */
Test(patterns, new_pattern_constant_in_x_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_x_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0.9, 0, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_x_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(1, 0, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_x_4)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(-0.1, 0, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_x_5)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(-1, 0, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, new_pattern_constant_in_x_6)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(-1.1, 0, 0);
	pattern = new_stripe_pattern(WHITE, BLACK);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
}

Test(patterns, lighting_with_stripe_pattern_applied)
{
	t_material	m;
	t_eye_normal view; 
	t_light		light;
	t_color		c1;
	t_color		c2;
	t_shape		shape;
	t_point		p;

	shape = new_sphere();
	m = material();
	m.pattern = new_stripe_pattern(new_color(1, 1, 1), new_color(0, 0, 0));
	m.ambient = new_color(1, 1, 1);
	m.diffuse = 0;
	m.specular = 0;
	shape.material = m;
	view.eyev = vector(0, 0, -1);
	view.normalv = vector(0, 0, -1);
	light = new_light(point(0, 0, -10), new_color(1, 1, 1));
	light.in_shadow = FALSE;
	p = new_point(0.9, 0, 0);
	c1 = lighting(&shape, &light, &p, &view);
	p = new_point(1.1, 0, 0);
	c2 = lighting(&shape, &light, &p, &view);
	
	cr_assert(eq(dbl, c1.r, 1));
	cr_assert(eq(dbl, c1.g, 1));
	cr_assert(eq(dbl, c1.b, 1));

	cr_assert(eq(dbl, c2.r, 0));
	cr_assert(eq(dbl, c2.g, 0));
	cr_assert(eq(dbl, c2.b, 0));
}
