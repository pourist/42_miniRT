#include "test.h"

Test(world, creating_world)
{
	t_world world;

	world = new_world();
	cr_assert(eq(ptr, world.objs, NULL));
	cr_assert(eq(ptr, world.objs, NULL));
}

Test(world, the_default_world)
{
	t_world	w;
	t_light	l;

	l = new_light(new_point(-10, 10, -10), new_color(1, 1, 1));
	w = default_world();
	cr_assert(eq(dbl, w.lights[0].position.x, l.position.x));
	cr_assert(eq(dbl, w.lights[0].position.y, l.position.y));
	cr_assert(eq(dbl, w.lights[0].position.z, l.position.z));
	cr_assert(eq(dbl, w.lights[0].intensity.r, l.intensity.r));
	cr_assert(eq(dbl, w.lights[0].intensity.g, l.intensity.g));
	cr_assert(eq(dbl, w.lights[0].intensity.b, l.intensity.b));

	cr_assert(eq(dbl, w.objs[0].material.color.r, 0.8));
	cr_assert(eq(dbl, w.objs[0].material.color.g, 1.0));
	cr_assert(eq(dbl, w.objs[0].material.color.b, 0.6));
	cr_assert(eq(dbl, w.objs[0].material.diffuse, 0.7));
	cr_assert(eq(dbl, w.objs[0].material.specular, 0.2));
	cr_assert(eq(dbl, w.objs[1].transform.mx[0][0], 0.5));
}

Test(world, intersect_world_with_ray)
{
	t_world	w;
	t_ray	r;
	t_hit	*xs;

	w = default_world();
	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	xs = intersect_world(&w, &r);
	cr_assert(eq(int, intersect_count(xs), 4));
	cr_assert(eq(dbl, xs->t, 4.0));
	cr_assert(eq(dbl, xs->next->t, 4.5));
	cr_assert(eq(dbl, xs->next->next->t, 5.5));
	cr_assert(eq(dbl, xs->next->next->next->t, 6.0));
}

Test(world, precomputing_state_of_intersection)
{
	t_shape		sphere;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;

	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	new_sphere(&sphere); 
	i = intersection(4, &sphere);
	comps = prepare_computations(i, &r, i);
	cr_assert(eq(dbl, comps.t, i->t));
	cr_assert(eq(ptr, comps.obj, i->obj));
	cr_assert(eq(int, tuple_eq(comps.point, new_point(0, 0, -1)), true));
	cr_assert(eq(int, tuple_eq(comps.view.eye_v, new_vector(0, 0, -1)), true));
	cr_assert(eq(int, tuple_eq(comps.view.normal_v, new_vector(0, 0, -1)), true));
}

Test(world, hit_when_intersection_occurs_on_outside)
{
	t_shape		sphere;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;

	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	new_sphere(&sphere); 
	i = intersection(4, &sphere);
	comps = prepare_computations(i, &r, i);
	cr_assert(eq(int, comps.inside, false));
}

Test(world, hit_when_intersection_occurs_on_inside)
{
	t_shape		sphere;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;

	r = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	new_sphere(&sphere); 
	i = intersection(1, &sphere);
	comps = prepare_computations(i, &r, i);
	cr_assert(eq(int, tuple_eq(comps.point, new_point(0, 0, 1)), true));
	cr_assert(eq(int, tuple_eq(comps.view.eye_v, new_vector(0, 0, -1)), true));
	cr_assert(eq(int, comps.inside, true));
	cr_assert(eq(int, tuple_eq(comps.view.normal_v, new_vector(0, 0, -1)), true));
}

Test(world, shading_an_intersection)
{
	t_world		w;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_color		c;
	t_color		expected;

	w = default_world();
	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	i = intersection(4, &w.objs[0]);
	comps = prepare_computations(i, &r, i);
	c = shade_hit(&w, &comps);
	expected = new_color(0.38066, 0.47583, 0.2855);
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, shading_an_intersection_from_the_inside)
{
	t_world		w;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_color		c;
	t_color		expected;

	w = default_world();
	w.lights[0] = new_light(new_point(0, 0.25, 0), new_color(1, 1, 1));
	r = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	i = intersection(0.5, &w.objs[1]);
	comps = prepare_computations(i, &r, i);
	c = shade_hit(&w, &comps);
	expected = new_color(0.90498, 0.90498, 0.90498);
	(void)c;
	(void)expected;
	// TODO: fix this test
	// cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	// cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	// cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, color_for_missed_ray)
{
	t_world	w;
	t_ray	r;
	t_color	c;
	t_color	expected;

	w = default_world();
	r = new_ray(new_point(0, 0, -5), new_vector(0, 1, 0));
	c = color_at(&w, &r);
	expected = new_color(0, 0, 0);
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, color_for_hit_ray)
{
	t_world	w;
	t_ray	r;
	t_color	c;
	t_color	expected;

	w = default_world();
	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	c = color_at(&w, &r);
	expected = new_color(0.38066, 0.47583, 0.2855);
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, color_with_intersection_behind_ray)
{
	t_world	w;
	t_shape	*outer; 
	t_shape	*inner; 
	t_ray	r;
	t_color	c;
	t_color	expected;

	w = default_world();
	outer = &w.objs[0];
	outer->material.ambient = new_color(1, 1, 1);
	inner = &w.objs[1];
	inner->material.ambient = new_color(1, 1, 1);
	r = new_ray(new_point(0, 0, 0.75), new_vector(0, 0, -1));
	c = color_at(&w, &r);
	expected = inner->material.color;
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, is_shadow_tests_for_occlusion_between_two_points)
{
	t_world	w;
	t_point	light_p;
	t_point	p;

	w = default_world();
	light_p = new_point(-10, -10, -10);
	p = new_point(-10, -10, 10);
	w.lights[0].position = light_p;
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
	p = new_point(10, 10, 10);
	w.lights[0].position = light_p;
	cr_assert(eq(int, is_shadowed(&w, &p, 0), true));
	p = new_point(-20, -20, -20);
	w.lights[0].position = light_p;
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
	p = new_point(-5, -5, -5);
	w.lights[0].position = light_p;
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
}

/*
 * Previous tests for hard shadows
Test(world, no_shadow_when_nothing_is_collinear_with_point_and_light)
{
	t_world	w;
	t_point	p;

	w = default_world();
	p = new_point(0, 10, 0);
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
}

Test(world, shadow_when_object_is_between_point_and_light)
{
	t_world	w;
	t_point	p;

	w = default_world();
	p = new_point(10, -10, 10);
	cr_assert(eq(int, is_shadowed(&w, &p, 0), true));
}

Test(world, no_shadow_when_object_is_behind_light)
{
	t_world	w;
	t_point	p;

	w = default_world();
	p = new_point(-20, 20, -20);
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
}

Test(world, no_shadow_when_object_is_behind_point)
{
	t_world	w;
	t_point	p;
	w = default_world();
	p = new_point(-2, 2, -2);
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
}

Test(world, shade_hit_is_given_an_intersection_in_shadow)
{
	t_world		w;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_color		c;
	t_color		expected;

	w = new_world();
	w.lights = malloc(sizeof(t_light));
	w.lights_count = 1;
	w.lights[0] = new_light(new_point(0, 0, -10), new_color(1, 1, 1));
	w.objs = malloc(sizeof(t_shape) * 2);
	w.objs_count = 2;
	new_sphere(&w.objs[0]);
	new_sphere(&w.objs[1]);
	set_transform(&w.objs[1], translation(0, 0, 10));
	r = new_ray(new_point(0, 0, 5), new_vector(0, 0, 1));
	i = intersection(4, &w.objs[1]);
	comps = prepare_computations(i, &r, i);
	c = shade_hit(&w, &comps);
	expected = new_color(0.1, 0.1, 0.1);
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
} */
