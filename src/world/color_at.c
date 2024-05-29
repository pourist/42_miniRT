#include "world.h"

t_point	point_on_light(t_light *light, double u, double v)
{
	return (add(light->corner, add(multiply(light->uvec, u + 0.5),
				multiply(light->vvec, v + 0.5))));
}

bool	is_shadowed(t_world *world, t_point *light_pos, t_point *point)
{
	t_vector	v;
	double		distance;
	t_ray		r;
	t_hit		*xs;
	t_hit		*h;

	v = subtract(*light_pos, *point);
	distance = sqrt(magnitude_squared(v));
	r = new_ray(*point, normalize(v));
	xs = intersect_world(world, &r);
	h = hit(xs);
	if (h && h->obj->cast_shadow == true && h->t < distance)
		return (true);
	return (false);
}

double	intensity_at(t_world *world, t_point *point, int index)
{
	double	total;
	double	u;
	double	v;
	t_point	light_position;

	if (world->lights[index].is_area_light == false)
	{
		if (is_shadowed(world, &world->lights[index].position, point))
			return (0.0);
		return (1.0);
	}
	total = 0.0;
	v = -1;
	while (++v < world->lights[index].vsteps)
	{
		u = -1;
		while (++u < world->lights[index].usteps)
		{
			light_position = point_on_light(&world->lights[index], u, v);
			if (!is_shadowed(world, &light_position, point))
				total += 1.0;
		}
	}
	return (total / world->lights[index].samples);
}

t_hit	*intersect_world(t_world *world, t_ray *ray)
{
	int		i;

	i = -1;
	world->xs = NULL;
	while (++i < world->objs_count && world->objs)
		intersect(&world->xs, &world->objs[i], ray);
	return (world->xs);
}

t_comps	prepare_computations(t_hit *intersect, t_ray *ray, t_hit *xs)
{
	t_comps	comps;

	comps.t = intersect->t;
	comps.obj = intersect->obj;
	comps.point = position(ray, comps.t);
	comps.view.eye_v = negate(normalize(ray->direction));
	comps.view.normal_v = normalize(normal_at(comps.obj, &comps.point));
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
		world->lights[i].global_intensity = intensity_at(
				world, &comps->over_point, i);
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
