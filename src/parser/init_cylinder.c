#include "parser.h"

/*
 Cylinder:
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
∗ identifier: cy
∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
∗ the cylinder diameter: 14.2
∗ the cylinder height: 21.42
∗ R,G,B colors in range [0,255]: 10, 0, 255
*/

void	make_cylinder(t_cylinder_info *cy, char **center, char **axis,
			t_shape *obj)
{
	t_vector		axis_v;
	t_vector		default_axis;
	t_matrix		trans_scale_m;
	t_matrix		rotation_m;
	t_matrix		transform_m;

	new_cylinder(obj);
	obj->cyl.min = 0;
	obj->cyl.max = 1;
	new_color(cy->r, cy->g, cy->b, &obj->material.color);
	new_vector(0, 1, 0, &default_axis);
	new_vector(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]), &axis_v);
	calculate_rotation_matrix(&default_axis, &axis_v, &rotation_m);
	multiply_matrices(translation(ft_atof(center[0]), ft_atof(center[1]),
			ft_atof(center[2]), &trans_scale_m), scaling(cy->diam, cy->height,
			cy->diam, &transform_m), &trans_scale_m);
	multiply_matrices(&rotation_m, &trans_scale_m, &transform_m);
	set_transform(obj, &transform_m);
	free_s(center);
	free_s(axis);
}

int	cy_info(t_line_parse_env *env, t_cylinder_info *cy)
{
	char	**rgb;

	cy->diam = ft_atof(env->line[3]);
	cy->height = ft_atof(env->line[4]);
	env->error_type = DIAM;
	if (solo(env->line[3], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = HEIGHT_VALID;
	if (solo(env->line[4], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[5], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	cy->r = (ft_atof(rgb[0]) / 255);
	cy->g = (ft_atof(rgb[1]) / 255);
	cy->b = (ft_atof(rgb[2]) / 255);
	return (free_s(rgb), 0);
}

int	init_cylinder(t_line_parse_env *env, t_shape *obj)
{
	t_cylinder_info	cy;
	char			**center;
	char			**axis;
	int		material;

	material = 0;
	if (ft_strarr_len(env->line) == 7)
		material = 1;
	else if (ft_strarr_len(env->line) != 6)
		return (file_error(env, ERR_CYLINDER));
	if (cy_info(env, &cy))
	{
		return (1);
	}
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = NORMAL;
	axis = ft_subsplit(env->line[2], ",\n");
	if (triplets(axis, -1, 1, env))
		return (free_s(center), 1);
	make_cylinder(&cy, center, axis, obj);
	if (material && find_material(env->material, obj, env->line[6], env))
		return (1);
	return (0);
}
