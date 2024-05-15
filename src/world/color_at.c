#include "world.h"

bool	is_shadowed(t_world *world, t_point *point, int index)
{
	t_vector	v;
	double		distance;
	t_ray		r;
	t_hit		*xs;
	t_hit		*h;

	v = subtract(world->lights[index].position, *point);
	distance = sqrt(magnitude_squared(v));
	r = new_ray(*point, normalize(v));
	xs = intersect_world(world, &r);
	h = hit(xs);
	if (h && h->obj->cast_shadow == true && h->t < distance)
		return (true);
	return (false);
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
	comps.view.eye_v = negate(normalize(ray->direction));
	comps.view.normal_v = normalize(normal_at(comps.obj, comps.point));
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

t_color	shade_hit(t_world *world, t_comps *comps)
{
	int		i;
	t_color	surface; 

	i = -1;
	surface = new_color(0, 0, 0);
	while (++i < world->lights_count)
	{
		world->lights[i].in_shadow = is_shadowed(world, &comps->over_point, i);
		surface = add_color(surface, lighting(comps->obj,
					&world->lights[i], &comps->over_point, &comps->view));
	}
	return (reflec_and_refrac(world, comps, &surface));
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
