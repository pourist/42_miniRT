/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:13:52 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/29 00:39:55 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_rotations(t_sphere_info *sp, t_matrix *transform_m)
{
	t_matrix	m;

	if (sp->trx != 0)
		rotation_x(cos(sp->trx), sin(sp->trx), &m);
	if (sp->try != 0)
		rotation_y(cos(sp->try), sin(sp->try), &m);
	if (sp->trz != 0)
		rotation_z(cos(sp->trz), sin(sp->trz), &m);
	if (sp->trx != 0 || sp->try != 0 || sp->trz != 0)
		multiply_matrices(&m, transform_m, transform_m);
}

void	make_sphere(t_sphere_info *sp, t_shape *obj)
{
	t_matrix	m1;
	t_matrix	m2;
	t_matrix	m3;
	t_matrix	final;

	new_sphere(obj);
	obj->cast_shadow = sp->cast_shadow;
	obj->material.color = sp->color;
	get_identity_matrix(&m1);
	set_rotations(sp, &m1);
	translation(sp->center.x, sp->center.y, sp->center.z, &m2);
	scaling(sp->diam * 0.5, sp->diam * 0.5, sp->diam * 0.5, &m3);
	multiply_matrices(&m1, &m2, &final);
	multiply_matrices(&final, &m3, &final);
	set_transform(obj, &final);
}

static bool	sp_info_2(t_line_parse_env *env, t_sphere_info *sp)
{
	char	**rgb;
	char	**center;

	env->error_type = DIAM;
	if (solo(env->line[2], EPSILON, (double)INT_MAX, env))
		return (false);
	sp->diam = ft_atof(env->line[2]);
	env->error_type = SHADOWS;
	if (solo(env->line[4], 0, 1, env))
		return (false);
	sp->cast_shadow = ft_atoi(env->line[4]);
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (free_s(center), false);
	new_point(ft_atof(center[0]), ft_atof(center[1]),
		ft_atof(center[2]), &sp->center);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[3], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (free_s(center), free_s(rgb), false);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255,
		ft_atof(rgb[2]) / 255, &sp->color);
	return (free_s(center), free_s(rgb), true);
}

static bool	sp_info_1(t_line_parse_env *env, t_sphere_info *sp, int *len)
{
	int	i;

	sp->trx = 0;
	sp->try = 0;
	sp->trz = 0;
	sp->material = false;
	if (*len >= 6)
	{
		i = 4;
		while (env->line[++i])
		{
			if (ft_strncmp(env->line[i], "Trx", 4) == 0)
				sp->trx = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Try", 4) == 0)
				sp->try = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Trz", 4) == 0)
				sp->trz = ft_atof(env->line[++i]);
			else if ((i == 5 && i == *len - 1) || (i == *len - 1
					&& (sp->trx != 0 || sp->try != 0 || sp->trz != 0)))
				sp->material = true;
			else
				return (false);
		}
	}
	return (true);
}

int	init_sphere(t_line_parse_env *env, t_shape *obj)
{
	t_sphere_info	sp;
	int				len;

	len = ft_strarr_len(env->line);
	if (!sp_info_1(env, &sp, &len) || len < 5)
		return (file_error(env, ERR_SPHERE));
	if (!sp_info_2(env, &sp))
		return (1);
	make_sphere(&sp, obj);
	if (sp.material
		&& find_material(env->material, obj, env->line[len - 1], env))
		return (1);
	return (0);
}
