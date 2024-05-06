#include "test.c"

Test(patterns, create_stripe_feature)
{
	t_pattern	pattern;
	t_color		white;
	t_color		black;
	t_color		res;
	t_point		p;
	
	pattern.a = malloc(sizeof(t_pattern));
	pattern.b = malloc(sizeof(t_pattern));
	*pattern.a = new_solid_pattern(WHITE);
	*pattern.b = new_solid_pattern(BLACK);
	white = new_color(1, 1, 1);
	black = new_color(0, 0, 0);
	p = new_point(0, 0, 0);

	res = pattern.a->pattern_at(pattern.a, &p);
	cr_assert(eq(dbl, res.r, white.r));
	cr_assert(eq(dbl, res.g, white.g));
	cr_assert(eq(dbl, res.b, white.b));
	res = pattern.b->pattern_at(pattern.b, &p);
	cr_assert(eq(dbl, res.r, black.r));
	cr_assert(eq(dbl, res.g, black.g));
	cr_assert(eq(dbl, res.b, black.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_y_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_y_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 1, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_y_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 2, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

/* A stripe pattern is constant in z */
Test(patterns, new_pattern_constant_in_z_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_z_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 1);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_z_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 2);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

/* A stripe pattern is constant in x */
Test(patterns, new_pattern_constant_in_x_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0, 0, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(0.9, 0, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(1, 0, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_4)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(-0.1, 0, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_5)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(-1, 0, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_6)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = new_point(-1.1, 0, 0);
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
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
	m = new_material();
	m.pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	m.ambient = new_color(1, 1, 1);
	m.diffuse = 0;
	m.specular = 0;
	shape.material = m;
	view.eye_v = new_vector(0, 0, -1);
	view.normal_v = new_vector(0, 0, -1);
	light = new_light(new_point(0, 0, -10), new_color(1, 1, 1));
	light.in_shadow = false;
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
	free(m.pattern.a);
	free(m.pattern.b);
}

Test(patterns, stripes_with_object_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;

	object = new_sphere();
	set_transform(&object, scaling(2, 2, 2));
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	p = new_point(1.5, 0, 0);
	res = pattern_at_shape(&pattern, &object, &p);
	expected = WHITE;

	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, stripes_with_pattern_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;

	object = new_sphere();
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	set_pattern_transform(&pattern, scaling(2, 2, 2));
	p = new_point(1.5, 0, 0);
	res = pattern_at_shape(&pattern, &object, &p);
	expected = WHITE;

	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, stripes_with_object_and_pattern_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;

	object = new_sphere();
	set_transform(&object, scaling(2, 2, 2));
	pattern = new_stripe_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	set_pattern_transform(&pattern, translation(0.5, 0, 0));
	p = new_point(2.5, 0, 0);
	res = pattern_at_shape(&pattern, &object, &p);
	expected = WHITE;

	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, gradient_linear_interpolation)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;

	pattern = new_gradient_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	p = new_point(0, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0.25, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = new_color(0.75, 0.75, 0.75);
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0.5, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = new_color(0.5, 0.5, 0.5);
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0.75, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = new_color(0.25, 0.25, 0.25);
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, ring_pattern)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	pattern = new_ring_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	p = new_point(0, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(1, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0, 0, 1);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0.708, 0, 0.708);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, checkers_should_repeat_in_x)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;

	pattern = new_checkers_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	p = new_point(0, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0.99, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(1.01, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, checkers_should_repeat_in_y)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;

	pattern = new_checkers_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	p = new_point(0, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0, 0.99, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0, 1.01, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, checkers_should_repeat_in_z)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;

	pattern = new_checkers_pattern(new_solid_pattern(WHITE),
		new_solid_pattern(BLACK));
	p = new_point(0, 0, 0);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0, 0, 0.99);
	res = pattern.pattern_at(&pattern, &p);
	expected = WHITE;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	p = new_point(0, 0, 1.01);
	res = pattern.pattern_at(&pattern, &p);
	expected = BLACK;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}
