#include "world.h"

t_world	new_world(void)
{
	return ((t_world){
		.xs = NULL,
		.objs_count = 0,
		.objs = NULL,
		.lights_count = 0,
		.lights = NULL,
		.ambient = new_color(0.1, 0.1, 0.1),
		.remaining_recursion = 5,
	});
}

t_hit	*intersect_world(t_world *world, t_ray *ray)
{
	int		i;

	i = -1;
	world->xs = NULL;
	while (++i < world->objs_count)
		intersect(&world->xs, &world->objs[i], *ray);
	return (world->xs);
}

t_comps	prepare_computations(t_hit *intersect, t_ray *ray, t_hit *xs)
{
	t_comps	comps;

	comps.t = intersect->t;
	comps.obj = intersect->obj;
	comps.point = position(*ray, comps.t);
	comps.view.eye_v = negate(ray->direction);
	comps.view.normal_v = normal_at(comps.obj, comps.point);
	comps.n1 = 1;
	comps.n2 = 1;
	if (dot(comps.view.normal_v, comps.view.eye_v) < 0)
	{
		comps.inside = true;
		comps.view.normal_v = negate(comps.view.normal_v);
	}
	else
		comps.inside = false;
	if (xs != NULL)
		find_refractive_indices(&comps, intersect, xs);
	comps.reflect_v = reflect(ray->direction, comps.view.normal_v);
	comps.over_point = add(comps.point, multiply(comps.view.normal_v, EPSILON));
	comps.under_point = subtract(comps.point,
			multiply(comps.view.normal_v, EPSILON));
	return (comps);
}

double	schlick(t_comps *comps)
{
	double	cos_i;
	double	n_ratio;
	double	sin2_t;
	double	cos_t;
	double	r0;

	cos_i = dot(comps->view.eye_v, comps->view.normal_v);
	if (comps->n1 > comps->n2)
	{
		n_ratio = comps->n1 / comps->n2;
		sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
		if (sin2_t > 1.0)
			return (1);
		cos_t = sqrt(1.0 - sin2_t);
		cos_i = cos_t;
	}
	r0 = pow((comps->n1 - comps->n2) / (comps->n1 + comps->n2), 2);
	return (r0 + (1 - r0) * pow(1 - cos_i, 5));
}

t_color	shade_hit(t_world *world, t_comps *comps)
{
	int		i;
	t_color	surface; 
	t_color	reflected;
	t_color	refracted;
	double	reflectance;

	if (!comps)
		return (new_color(0, 0, 0));
	i = -1;
	surface = new_color(0, 0, 0);
	while (++i < world->lights_count)
	{
		world->lights[i].in_shadow = is_shadowed(world, &comps->over_point, i);
		surface = add_color(surface, lighting(comps->obj,
					&world->lights[i], &comps->over_point, &comps->view));
	}
	reflected = reflected_color(world, comps);
	refracted = refracted_color(world, comps);
	if (comps->obj->material.reflective > 0 && comps->obj->material.transparency > 0)
	{
		reflectance = schlick(comps);
		return (add_color(surface, add_color(
					multiply_color(reflected, reflectance),
					multiply_color(refracted, 1.0 - reflectance))));
	}
	return (add_color(add_color(surface, reflected), refracted));
}

t_color	color_at(t_world *world, t_ray *ray)
{
	t_hit	*intersect;
	t_comps	comps;

	intersect_world(world, ray);
	intersect = hit(world->xs);
	if (!intersect)
		return (new_color(0, 0, 0));
	comps = prepare_computations(intersect, ray, world->xs);
	return (shade_hit(world, &comps));
}
