#include "lights.h"

t_light	new_light(t_point position, t_color intensity)
{
	return ((t_light){
		position,
		intensity,
		.global_intensity = 1.0,
	});
}

t_light	area_light(t_area_light_params *lp)
{
	t_light	light;

	light.corner = lp->corner;
	light.uvec = multiply(lp->full_uvec, 1.0 / lp->usteps);
	light.usteps = lp->usteps;
	light.vvec = multiply(lp->full_vvec, 1.0 / lp->vsteps);
	light.vsteps = lp->vsteps;
	light.samples = lp->usteps * lp->vsteps;
	light.intensity = lp->intensity;
	light.position = add(lp->corner,
			add(multiply(lp->full_uvec, 0.5), multiply(lp->full_vvec, 0.5)));
	return (light);
}
