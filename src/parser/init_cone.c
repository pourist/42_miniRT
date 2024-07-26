/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:40:20 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/25 12:07:49 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	make_cone(t_cone_info *cone, char **center, char **axis, t_shape *obj)
{
	t_vector		axis_v;
	t_vector		default_axis;
	t_matrix		trans_scale_m;
	t_matrix		rotation_m;
	t_matrix		transform_m;

	new_cone(obj);
	obj->cone.min = -1;
	obj->cone.max = 0;
	obj->cone.closed = !cone->open;
	obj->cast_shadow = cone->cast_shadow;
	new_color(cone->r, cone->g, cone->b, &obj->material.color);
	new_vector(0, 1, 0, &default_axis);
	new_vector(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]), &axis_v);
	calculate_rotation_matrix(&default_axis, &axis_v, &rotation_m);
	multiply_matrices(translation(ft_atof(center[0]), ft_atof(center[1])
			+ (cone->height * 0.5), ft_atof(center[2]), &trans_scale_m),
		scaling(cone->diam, cone->height, cone->diam,
			&transform_m), &trans_scale_m);
	multiply_matrices(&rotation_m, &trans_scale_m, &transform_m);
	set_transform(obj, &transform_m);
	free_s(center);
	free_s(axis);
}

int	cone_info(t_line_parse_env *env, t_cone_info *cone)
{
	char	**rgb;

	cone->diam = ft_atof(env->line[3]);
	cone->height = ft_atof(env->line[4]);
	env->error_type = DIAM;
	if (solo(env->line[3], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = HEIGHT_VALID;
	if (solo(env->line[4], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = OPEN;
	if (solo(env->line[6], 0, 1, env))
		return (1);
	cone->open = ft_atoi(env->line[6]);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[5], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	cone->r = (ft_atof(rgb[0]) / 255);
	cone->g = (ft_atof(rgb[1]) / 255);
	cone->b = (ft_atof(rgb[2]) / 255);
	if (env->line[7])
		cone->cast_shadow = ft_atoi(env->line[7]);
	return (free_s(rgb), 0);
}

int	init_cone(t_line_parse_env *env, t_shape *obj)
{
	t_cone_info	cone;
	char		**axis;
	char		**center;
	int			material;

	material = 0;
	if (ft_strarr_len(env->line) == 9)
		material = 1;
	else if (ft_strarr_len(env->line) < 7 && ft_strarr_len(env->line) > 9)
		return (file_error(env, ERR_CONE));
	if (cone_info(env, &cone))
		return (1);
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = NORMAL_;
	axis = ft_subsplit(env->line[2], ",\n");
	if (triplets(axis, -1, 1, env))
		return (free_s(center), 1);
	make_cone(&cone, center, axis, obj);
	if (material && find_material(env->material, obj, env->line[8], env))
		return (1);
	return (0);
}
