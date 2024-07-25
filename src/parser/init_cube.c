/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:26:38 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/25 11:59:33 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	make_cube(t_cube_info *cube, char **center, char **axis, t_shape *obj)
{
	t_vector	axis_v;
	t_vector	default_axis;
	t_matrix	m[4];

	new_cube(obj);
	new_color(cube->r, cube->g, cube->b, &obj->material.color);
	new_vector(0, 1, 0, &default_axis);
	new_vector(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]), &axis_v);
	calculate_rotation_matrix(&default_axis, &axis_v, &m[2]);
	translation(ft_atof(center[0]), ft_atof(center[1]),
		ft_atof(center[2]), &m[0]);
	scaling(cube->width, cube->height, cube->depth, &m[1]);
	multiply_matrices(&m[2], &m[0], &m[3]);
	multiply_matrices(&m[3], &m[1], &m[3]);
	set_transform(obj, &m[3]);
	obj->cast_shadow = cube->cast_shadow;
}

int	cube_info(t_line_parse_env *env, t_cube_info *cube)
{
	char	**rgb;

	cube->depth = ft_atof(env->line[5]);
	cube->height = ft_atof(env->line[4]);
	cube->width = ft_atof(env->line[3]);
	env->error_type = HEIGHT_VALID;
	if (solo(env->line[4], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = WIDTH_VALID;
	if (solo(env->line[3], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = DEPTH_VALID;
	if (solo(env->line[5], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[6], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	cube->r = (ft_atof(rgb[0]) / 255);
	cube->g = (ft_atof(rgb[1]) / 255);
	cube->b = (ft_atof(rgb[2]) / 255);
	if (env->line[7])
		cube->cast_shadow = ft_atoi(env->line[7]);
	free_s(rgb);
	return (0);
}

int	init_cube(t_line_parse_env *env, t_shape *obj)
{
	t_cube_info	cube;
	char		**center;
	char		**norm;
	int			material;

	material = 0;
	if (ft_strarr_len(env->line) == 9)
		material = 1;
	else if (ft_strarr_len(env->line) < 7 || ft_strarr_len(env->line) > 9)
		return (file_error(env, ERR_CUBE));
	if (cube_info(env, &cube))
		return (1);
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = NORMAL_;
	norm = ft_subsplit(env->line[2], ",\n");
	if (triplets(norm, -1, 1, env))
		return (free_s(center), 1);
	make_cube(&cube, center, norm, obj);
	if (material && find_material(env->material, obj, env->line[8], env))
		return (free_s(norm), free_s(center), 1);
	return (free_s(norm), free_s(center), 0);
}
