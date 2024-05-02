#ifndef MATERIALS_H
# define MATERIALS_H

# include "lights.h"

typedef struct s_material
{
	t_color	color;
	t_color	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_lighting_params
{
	t_color		effective_color;
	t_vector	light_v;
	t_vector	reflect_v;
	double		light_dot_normal;
	double		reflect_dot_eye;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
}	t_lighting_params;

t_material	new_material(void);

#endif
