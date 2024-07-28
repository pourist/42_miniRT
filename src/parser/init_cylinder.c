/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:45:14 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/28 21:18:30 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_rotations(t_cylinder_info *cy, t_matrix *transform_m)
{
	t_matrix	m;

	if (cy->trx != 0)
		rotation_x(cos(cy->trx), sin(cy->trx), &m);
	if (cy->try != 0)
		rotation_y(cos(cy->try), sin(cy->try), &m);
	if (cy->trz != 0)
		rotation_z(cos(cy->trz), sin(cy->trz), &m);
	if (cy->trx != 0 || cy->try != 0 || cy->trz != 0)
		multiply_matrices(&m, transform_m, transform_m);
}

void	make_cylinder(t_cylinder_info *cy, char **center, char **axis,
			t_shape *obj)
{
	t_vector		axis_v;
	t_vector		default_axis;
	t_matrix		trans_scale_m;
	t_matrix		rotation_m;
	t_matrix		transform_m;

	new_cylinder(obj);
	obj->cyl.min = -0.5;
	obj->cyl.max = 0.5;
	obj->cyl.closed = !cy->open;
	obj->cast_shadow = cy->cast_shadow;
	obj->material.color = cy->color;
	new_vector(0, 1, 0, &default_axis);
	new_vector(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]), &axis_v);
	calculate_rotation_matrix(&default_axis, &axis_v, &rotation_m);
	get_identity_matrix(&transform_m);
	set_rotations(cy, &transform_m);
	multiply_matrices(&transform_m, &rotation_m, &rotation_m);
	multiply_matrices(translation(ft_atof(center[0]), ft_atof(center[1]),
			ft_atof(center[2]), &trans_scale_m), scaling(cy->diam, cy->height,
			cy->diam, &transform_m), &trans_scale_m);
	multiply_matrices(&rotation_m, &trans_scale_m, &transform_m);
	set_transform(obj, &transform_m);
	free_s(center);
	free_s(axis);
}

int	cy_info_2(t_line_parse_env *env, t_cylinder_info *cy)
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
	env->error_type = OPEN;
	if (solo(env->line[6], 0, 1, env))
		return (1);
	cy->open = ft_atoi(env->line[6]);
	env->error_type = SHADOWS;
	if (solo(env->line[7], 0, 1, env))
		return (1);
	cy->cast_shadow = ft_atoi(env->line[7]);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[5], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255,
		ft_atof(rgb[2]) / 255, &cy->color);
	return (free_s(rgb), 0);
}

static bool	cy_info_1(t_line_parse_env *env, t_cylinder_info *cy, int *len)
{
	int	i;

	cy->trx = 0;
	cy->try = 0;
	cy->trz = 0;
	cy->material = false;
	if (*len >= 9)
	{
		i = 7;
		while (env->line[++i])
		{
			if (ft_strncmp(env->line[i], "Trx", 4) == 0)
				cy->trx = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Try", 4) == 0)
				cy->try = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Trz", 4) == 0)
				cy->trz = ft_atof(env->line[++i]);
			else if ((i == 8 && i == *len - 1) || (i == *len - 1
					&& (cy->trx != 0 || cy->try != 0 || cy->trz != 0)))
				cy->material = true;
			else
				return (false);
		}
	}
	return (true);
}

int	init_cylinder(t_line_parse_env *env, t_shape *obj)
{
	t_cylinder_info	cy;
	char			**center;
	char			**axis;
	int				len;

	len = ft_strarr_len(env->line);
	if (!cy_info_1(env, &cy, &len) || len < 8)
		return (file_error(env, ERR_CONE));
	if (cy_info_2(env, &cy))
		return (1);
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = NORMAL_;
	axis = ft_subsplit(env->line[2], ",\n");
	if (triplets(axis, -1, 1, env))
		return (free_s(center), 1);
	make_cylinder(&cy, center, axis, obj);
	if (cy.material && find_material(env->material, obj, env->line[8], env))
		return (1);
	return (0);
}
