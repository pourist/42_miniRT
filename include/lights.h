#ifndef LIGHTS_H
# define LIGHTS_H

# include <stdbool.h>

# include "tuples.h"
# include "utils.h"

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

#endif
