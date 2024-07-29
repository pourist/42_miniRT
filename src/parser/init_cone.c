/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:40:20 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/29 08:22:15 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_rotations(t_cone_info *cone, t_matrix *transform_m)
{
	t_matrix	m;

	if (cone->trx != 0)
		rotation_x(cos(cone->trx), sin(cone->trx), &m);
	if (cone->try != 0)
		rotation_y(cos(cone->try), sin(cone->try), &m);
	if (cone->trz != 0)
		rotation_z(cos(cone->trz), sin(cone->trz), &m);
	if (cone->trx != 0 || cone->try != 0 || cone->trz != 0)
		multiply_matrices(&m, transform_m, transform_m);
}

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
	obj->material.color = cone->color;
	new_vector(0, 1, 0, &default_axis);
	new_vector(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]), &axis_v);
	calculate_rotation_matrix(&default_axis, &axis_v, &rotation_m);
	get_identity_matrix(&transform_m);
	set_rotations(cone, &transform_m);
	multiply_matrices(&transform_m, &rotation_m, &rotation_m);
	multiply_matrices(translation(ft_atof(center[0]), ft_atof(center[1])
			+ (cone->height * 0.5), ft_atof(center[2]), &trans_scale_m),
		scaling(cone->diam, cone->height, cone->diam,
			&transform_m), &trans_scale_m);
	multiply_matrices(&rotation_m, &trans_scale_m, &transform_m);
	set_transform(obj, &transform_m);
}

static bool	cone_info_2(t_line_parse_env *env, t_cone_info *cone)
{
	char	**rgb;

	cone->diam = ft_atof(env->line[3]);
	cone->height = ft_atof(env->line[4]);
	env->error_type = DIAM;
	if (solo(env->line[3], EPSILON, (double)INT_MAX, env))
		return (false);
	env->error_type = HEIGHT_VALID;
	if (solo(env->line[4], EPSILON, (double)INT_MAX, env))
		return (false);
	env->error_type = OPEN;
	if (solo(env->line[6], 0, 1, env))
		return (false);
	cone->open = ft_atoi(env->line[6]);
	env->error_type = SHADOWS;
	if (solo(env->line[7], 0, 1, env))
		return (false);
	cone->cast_shadow = ft_atoi(env->line[7]);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[5], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (false);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255,
		ft_atof(rgb[2]) / 255, &cone->color);
	return (free_s(rgb), true);
}

static bool	cone_info_1(t_line_parse_env *env, t_cone_info *c, int *len)
{
	int	i;

	c->trx = 0;
	c->try = 0;
	c->trz = 0;
	c->material = false;
	if (*len >= 9)
	{
		i = 7;
		while (env->line[++i])
		{
			if (ft_strncmp(env->line[i], "Trx", 4) == 0)
				c->trx = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Try", 4) == 0)
				c->try = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Trz", 4) == 0)
				c->trz = ft_atof(env->line[++i]);
			else if ((i == 8 && i == *len - 1) || (i == *len - 1
					&& (c->trx != 0 || c->try != 0 || c->trz != 0)))
				c->material = true;
			else
				return (false);
		}
	}
	return (true);
}

int	init_cone(t_line_parse_env *env, t_shape *obj)
{
	t_cone_info	cone;
	char		**axis;
	char		**center;
	int			len;

	len = ft_strarr_len(env->line);
	if (!cone_info_1(env, &cone, &len) || len < 8)
		return (file_error(env, ERR_CONE));
	if (!cone_info_2(env, &cone))
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
	if (cone.material
		&& find_material(env->material, obj, env->line[len - 1], env))
		return (free_s(center), free_s(axis), 1);
	return (free_s(center), free_s(axis), 0);
}
