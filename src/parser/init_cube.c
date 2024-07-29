/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:26:38 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/29 08:23:38 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_rotations(t_cube_info *cube, t_matrix *transform_m)
{
	t_matrix	m;

	if (cube->trx != 0)
		rotation_x(cos(cube->trx), sin(cube->trx), &m);
	if (cube->try != 0)
		rotation_y(cos(cube->try), sin(cube->try), &m);
	if (cube->trz != 0)
		rotation_z(cos(cube->trz), sin(cube->trz), &m);
	if (cube->trx != 0 || cube->try != 0 || cube->trz != 0)
		multiply_matrices(&m, transform_m, transform_m);
}

void	make_cube(t_cube_info *cube, char **center, char **axis, t_shape *obj)
{
	t_vector	axis_v;
	t_vector	default_axis;
	t_matrix	m[4];

	new_cube(obj);
	obj->cast_shadow = cube->cast_shadow;
	obj->material.color = cube->color;
	new_vector(0, 1, 0, &default_axis);
	new_vector(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]), &axis_v);
	calculate_rotation_matrix(&default_axis, &axis_v, &m[2]);
	get_identity_matrix(&m[3]);
	set_rotations(cube, &m[3]);
	multiply_matrices(&m[3], &m[2], &m[2]);
	translation(ft_atof(center[0]), ft_atof(center[1]),
		ft_atof(center[2]), &m[0]);
	scaling(cube->width, cube->height, cube->depth, &m[1]);
	multiply_matrices(&m[2], &m[1], &m[1]);
	multiply_matrices(&m[0], &m[1], &m[3]);
	set_transform(obj, &m[3]);
}

static bool	cube_info_2(t_line_parse_env *env, t_cube_info *cube)
{
	char	**rgb;

	cube->depth = ft_atof(env->line[5]);
	cube->height = ft_atof(env->line[4]);
	cube->width = ft_atof(env->line[3]);
	env->error_type = HEIGHT_VALID;
	if (solo(env->line[4], EPSILON, (double)INT_MAX, env))
		return (false);
	env->error_type = WIDTH_VALID;
	if (solo(env->line[3], EPSILON, (double)INT_MAX, env))
		return (false);
	env->error_type = DEPTH_VALID;
	if (solo(env->line[5], EPSILON, (double)INT_MAX, env))
		return (false);
	env->error_type = SHADOWS;
	if (solo(env->line[7], 0, 1, env))
		return (false);
	cube->cast_shadow = ft_atoi(env->line[7]);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[6], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (false);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255,
		ft_atof(rgb[2]) / 255, &cube->color);
	return (free_s(rgb), true);
}

static bool	cube_info_1(t_line_parse_env *env, t_cube_info *c, int *len)
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

int	init_cube(t_line_parse_env *env, t_shape *obj)
{
	t_cube_info	cube;
	char		**center;
	char		**norm;
	int			len;

	len = ft_strarr_len(env->line);
	if (!cube_info_1(env, &cube, &len) || len < 8)
		return (file_error(env, ERR_CUBE));
	if (!cube_info_2(env, &cube))
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
	if (cube.material && find_material(env->material, obj,
			env->line[len - 1], env))
		return (free_s(norm), free_s(center), 1);
	return (free_s(norm), free_s(center), 0);
}
