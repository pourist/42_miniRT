#ifndef LIGHTS_H
# define LIGHTS_H

# include <stdbool.h>

# include "tuples.h"
# include "utils.h"
# include "shapes.h"

typedef struct s_light
{
	t_point		position;
	t_color		intensity;
	double		intensity_ratio;
	t_point		corner;
	t_vector	uvec;
	int			usteps;
	t_vector	vvec;
	int			vsteps;
	int			samples;
	double		inverse_samples;
	t_sequencer	jitter_by;
	bool		is_area_light;
}	t_light;

typedef struct s_eye_normal
{
	t_vector	eye_v;
	t_vector	normal_v;
}	t_eye_normal;

typedef struct s_alight_params
{
	t_point		corner;
	t_vector	full_uvec;
	int			usteps;
	t_vector	full_vvec;
	int			vsteps;
	t_color		intensity;
}	t_alight_params;

t_light	new_light(t_point position, t_color intensity);
void	new_area_light(t_alight_params *lp, t_light *light);
// Material.c 
t_color	lighting(t_shape *shape, t_light *light, t_point *point,
			t_eye_normal *view);
t_color	area_lighting(t_shape *s, t_light *l, t_point *p, t_eye_normal *v);

#endif
