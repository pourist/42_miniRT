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

void	find_refractive_indices(t_comps *comps, t_hit *i, t_hit *xs)
{
	t_hit	*containers;
	int	size;
	int	x;
	
	size = intersect_count(xs);
	containers = (t_hit *)malloc(sizeof(t_hit) * size);
	if (!containers)
		return ;
	x = -1;
	// while (++x )
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
	comps.over_point = add(comps.point, multiply(comps.view.normal_v, EPSILON));
	comps.reflect_v = reflect(ray->direction, comps.view.normal_v);
	return (comps);
}

t_color	shade_hit(t_world *world, t_comps *comps)
{
	int		i;
	t_color	surface; 
	t_color	reflected;

	i = -1;
	surface = new_color(0, 0, 0);
	while (++i < world->lights_count)
	{
		world->lights[i].in_shadow = is_shadowed(world, &comps->over_point, i);
		surface = add_color(surface, lighting(comps->obj,
					&world->lights[i], &comps->over_point, &comps->view));
	}
	reflected = reflected_color(world, comps);
	return (add_color(surface, reflected));
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
