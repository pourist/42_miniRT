#include "lights.h"

t_light	new_light(t_point position, t_color intensity)
{
	return ((t_light){
		position,
		intensity,
		.in_shadow = false
	});
}
