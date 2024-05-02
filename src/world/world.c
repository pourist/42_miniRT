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

t_comps	prepare_computations(t_hit *intersect, t_ray *ray)
{
	t_comps	comps;

	comps.t = intersect->t;
	comps.obj = intersect->obj;
	comps.point = position(*ray, comps.t);
	comps.view.eye_v = negate(ray->direction);
	comps.view.normal_v = normal_at(comps.obj, comps.point);
	if (dot(comps.view.normal_v, comps.view.eye_v) < 0)
	{
		comps.inside = true;
		comps.view.normal_v = negate(comps.view.normal_v);
	}
	else
		comps.inside = false;
	comps.over_point = add(comps.point, multiply(comps.view.normal_v, EPSILON));
	return (comps);
}

t_color	shade_hit(t_world *world, t_comps *comps)
{
	int		i;
	t_color	color;

	i = -1;
	color = new_color(0, 0, 0);
	while (++i < world->lights_count)
	{
		world->lights[i].in_shadow = is_shadowed(world, &comps->over_point, i);
		color = add_color(color, lighting(&comps->obj->material,
					&world->lights[i], &comps->point, &comps->view));
	}
	return (color);
}

t_color	color_at(t_world *world, t_ray *ray)
{
	t_hit	*intersect;
	t_comps	comps;

	intersect_world(world, ray);
	intersect = hit(world->xs);
	if (!intersect)
		return (world->ambient);
	comps = prepare_computations(intersect, ray);
	return (shade_hit(world, &comps));
}
