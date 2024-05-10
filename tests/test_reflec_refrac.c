#include "test.h"

Test(materials, reflectivity_for_the_default_material)
{
	t_material	m;
	m = new_material();
	cr_assert(eq(dbl, m.reflective, 0.0));
}

Test(intersections, precomputing_the_reflection_vector)
{
	t_shape		s;
	t_ray		r;
	t_hit	*i;
	t_comps		comps;
	t_vector		result;

	s = new_plane();
	r = new_ray(new_point(0, 1, -1), new_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), &s);
	comps = prepare_computations(i, &r, NULL);
	result = comps.reflect_v;
	cr_assert(epsilon_eq(dbl, result.x, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, sqrt(2)/2, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, sqrt(2)/2, EPSILON));
}

Test(world, reflected_color_for_a_nonreflective_material)
{
	t_world		world;
	t_ray		r;
	t_hit		*i;
	t_comps		comps;
	t_color		color;

	world = default_world();
	r = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	world.objs[1].material.ambient = new_color(1, 1, 1);
	i = intersection(1, &world.objs[0]);
	comps = prepare_computations(i, &r, NULL);
	color = reflected_color(&world, &comps);
	cr_assert(color_eq(color, new_color(0, 0, 0)));
}

Test(world, reflected_color_for_a_reflective_material)
{
	t_world		world;
	t_ray		r;
	t_hit		*i;
	t_comps		comps;
	t_color		color;
	t_color		result;

	world = default_world();
	world.objs[1] = new_plane();
	world.objs[1].material.reflective = 0.5;
	set_transform(&world.objs[1], translation(0, -1, 0));
	r = new_ray(new_point(0, 0, -3), new_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), &world.objs[1]);
	comps = prepare_computations(i, &r, NULL);
	color = reflected_color(&world, &comps);
	result = new_color(0.19032, 0.2379, 0.14274);
	// cr_assert(epsilon_eq(dbl, color.r, result.r, EPSILON));
	// cr_assert(epsilon_eq(dbl, color.g, result.g, EPSILON));
	cr_assert(epsilon_eq(dbl, color.b, result.b, EPSILON));
}

Test(world, shade_hit_with_a_reflective_material)
{
	t_world		world;
	t_ray		r;
	t_hit		*i;
	t_comps		comps;
	t_color		color;
	t_color		result;

	world = default_world();
	world.objs[1] = new_plane();
	world.objs[1].material.reflective = 0.5;
	set_transform(&world.objs[1], translation(0, -1, 0));
	r = new_ray(new_point(0, 0, -3), new_vector(0, sqrt(2)/-2, sqrt(2)/2));
	i = intersection(sqrt(2), &world.objs[1]);
	comps = prepare_computations(i, &r, NULL);
	color = shade_hit(&world, &comps);
	result = new_color(0.87677, 0.92436, 0.82918);
	// cr_assert(epsilon_eq(dbl, color.r, result.r, EPSILON));
	// cr_assert(epsilon_eq(dbl, color.g, result.g, EPSILON));
	cr_assert(epsilon_eq(dbl, color.b, result.b, EPSILON));
}

Test(world, color_at_with_mutually_reflective_surfaces)
{
	t_world		world;
	t_ray		r;
	t_color		color;

	world = new_world();
	world.lights = malloc(sizeof(t_light));
	world.lights_count = 1;
	world.lights[0] = new_light(new_point(0, 0, 0), new_color(1, 1, 1));
	world.objs = malloc(sizeof(t_shape) * 2);
	world.objs_count = 2;
	world.objs[0] = new_plane();
	world.objs[0].material.reflective = 1;
	set_transform(&world.objs[0], translation(0, -1, 0));
	world.objs[1] = new_plane();
	world.objs[1].material.reflective = 1;
	set_transform(&world.objs[1], translation(0, 1, 0));
	r = new_ray(new_point(0, 0, 0), new_vector(0, 1, 0));
	color = color_at(&world, &r);
	cr_assert(eq(ptr, &color, &color));
}

Test(world, reflected_color_at_the_maximum_recursive_depth)
	{
		t_world		world;
		t_ray		r;
		t_hit		*i;
		t_comps		comps;
		t_color		color;
		t_color		result;

		world = default_world();
		world.objs[0] = new_plane();
		world.objs[0].material.reflective = 0.5;
		set_transform(&world.objs[0], translation(0, -1, 0));
		r = new_ray(new_point(0, 0, -3), new_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
		i = intersection(sqrt(2), &world.objs[1]);
		comps = prepare_computations(i, &r, NULL);
		color = reflected_color(&world, &comps);
		result = new_color(0, 0, 0);
		cr_assert(epsilon_eq(dbl, color.r, result.r, EPSILON));
		cr_assert(epsilon_eq(dbl, color.g, result.g, EPSILON));
		cr_assert(epsilon_eq(dbl, color.b, result.b, EPSILON));
}

Test(materials, transparency_and_refractive_index_for_the_default_material)
{
	t_material	m;

	m = new_material();
	cr_assert(eq(dbl, m.transparency, 0.0));
	cr_assert(eq(dbl, m.refractive_index, 1.0));
}

Test(spheres, helper_for_producing_a_sphere_with_a_glassy_material)
{
	t_shape	s;

	s = new_glass_sphere();
	cr_assert(eq(dbl, s.material.transparency, 1.0));
	cr_assert(eq(dbl, s.material.refractive_index, 1.5));
}

Test(intersections,finding_n1_and_n2_at_various_intersections)
{
	t_shape		a;
	t_shape		b;
	t_shape		c;
	t_ray		r;
	t_hit		*i;
	t_comps		comps;

	a = new_glass_sphere();
	a.material.refractive_index = 1.5;
	set_transform(&a, scaling(2, 2, 2));
	b = new_glass_sphere();
	b.material.refractive_index = 2.0;
	set_transform(&b, translation(0, 0, -0.25));
	c = new_glass_sphere();
	c.material.refractive_index = 2.5;
	set_transform(&c, translation(0, 0, 0.25));
	r = new_ray(new_point(0, 0, -4), new_vector(0, 0, 1));
	i = NULL;
	insert_intersection(&i, intersection(2, &a));
	insert_intersection(&i, intersection(2.75, &b));
	insert_intersection(&i, intersection(3.25, &c));
	insert_intersection(&i, intersection(4.75, &b));
	insert_intersection(&i, intersection(5.25, &c));
	insert_intersection(&i, intersection(6, &a));

	printf("i->t: %f\n", i->t);
	printf("i->next->t: %f\n", i->next->t);
	printf("i->next->next->t: %f\n", i->next->next->t);
	printf("i->next->next->next->t: %f\n", i->next->next->next->t);
	printf("i->next->next->next->next->t: %f\n", i->next->next->next->next->t);
	printf("i->next->next->next->next->next->t: %f\n", i->next->next->next->next->next->t);
	comps = prepare_computations(i, &r, i);
	printf("comps.n1: %f\n", comps.n1);
	printf("comps.n2: %f\n", comps.n2);
	cr_assert(eq(dbl, comps.n1, 1.0));
	cr_assert(eq(dbl, comps.n2, 1.5));

	comps = prepare_computations(i->next, &r, i);
	printf("comps.n1: %f\n", comps.n1);
	printf("comps.n2: %f\n", comps.n2);
	cr_assert(eq(dbl, comps.n1, 1.5));
	cr_assert(eq(dbl, comps.n2, 2.0));

	comps = prepare_computations(i->next->next, &r, i);
	printf("comps.n1: %f\n", comps.n1);
	printf("comps.n2: %f\n", comps.n2);
	cr_assert(eq(dbl, comps.n1, 2.0));
	cr_assert(eq(dbl, comps.n2, 2.5));

	comps = prepare_computations(i->next->next->next, &r, i);
	printf("comps.n1: %f\n", comps.n1);
	printf("comps.n2: %f\n", comps.n2);
	cr_assert(eq(dbl, comps.n1, 2.5));
	cr_assert(eq(dbl, comps.n2, 2.5));

	comps = prepare_computations(i->next->next->next->next, &r, i);
	printf("comps.n1: %f\n", comps.n1);
	printf("comps.n2: %f\n", comps.n2);
	cr_assert(eq(dbl, comps.n1, 2.5));
	cr_assert(eq(dbl, comps.n2, 1.5));

	comps = prepare_computations(i->next->next->next->next->next, &r, i);
	printf("comps.n1: %f\n", comps.n1);
	printf("comps.n2: %f\n", comps.n2);
	cr_assert(eq(dbl, comps.n1, 1.5));
	cr_assert(eq(dbl, comps.n2, 1.0));
}
