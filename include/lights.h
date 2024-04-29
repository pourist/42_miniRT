#ifndef LIGHTS_H
# define LIGHTS_H

# include "tuples.h"

typedef struct s_light
{
	t_point	position;
	t_color	intensity;
}	t_light;

typedef struct s_eye_normal
{
	t_vector	eye_v;
	t_vector	normal_v;
}	t_eye_normal;

t_light	new_light(t_point position, t_color intensity);

#endif
