#include "world.h"

t_world	new_world(t_shape *world)
{
	return ((t_world){
		xs = NULL,
		objs_count = 0,
		objs = NULL,
		lights_count = 0,
		elements_inside = NULL,
		lights = NULL,
		ambient = new_color(0.1, 0.1, 0.1),
		.remaining_recursion = MAX_RECURSION,
	});
}
