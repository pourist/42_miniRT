#include "lights.h"

t_light	*new_light(t_point *position, t_color *intensity, t_light *light)
{
	light->position = *position;
	light->intensity = *intensity;
	light->intensity_ratio = 1.0;
	light->is_area_light = false;
	new_point(0.0, 0.0, 0.0, &light->corner);
	new_vector(0.0, 0.0, 0.0, &light->uvec);
	new_vector(0.0, 0.0, 0.0, &light->vvec);
	light->usteps = 1;
	light->vsteps = 1;
	light->samples = 1;
	return (light);
}

t_light	*new_area_light(t_alight_params *lp, t_light *light)
{
	t_vector	tmp;

	light->is_area_light = true;
	light->corner = lp->corner;
	multiply(&lp->full_uvec, 1.0 / lp->usteps, &light->uvec);
	light->usteps = lp->usteps;
	multiply(&lp->full_vvec, 1.0 / lp->vsteps, &light->vvec);
	light->vsteps = lp->vsteps;
	light->samples = lp->usteps * lp->vsteps;
	light->inverse_samples = 1.0 / light->samples;
	light->intensity = lp->intensity;
	add(&lp->corner, add(multiply(&lp->full_uvec, 0.5, &light->position),
			multiply(&lp->full_vvec, 0.5, &tmp), &tmp), &light->position);
	light->intensity_ratio = 1.0;
	new_sequencer(&light->jitter_by);
	return (light);
}
