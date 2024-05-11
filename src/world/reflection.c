#include "world.h"

t_color	reflected_color(t_world *world, t_comps *comps)
{
	t_ray	reflect_ray;
	t_color	color;

	if (comps->obj->material.reflective == 0 || world->remaining_recursion <= 0)
		return (new_color(0, 0, 0));
	reflect_ray = new_ray(comps->over_point, comps->reflect_v);
	world->remaining_recursion--;
	color = color_at(world, &reflect_ray);
	return (multiply_color(color, comps->obj->material.reflective));
}
