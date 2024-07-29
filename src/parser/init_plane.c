/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:11:45 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/29 08:28:46 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_rotations(t_plane_info *pl, t_matrix *transform_m)
{
	t_matrix	m;

	if (pl->trx != 0)
		rotation_x(cos(pl->trx), sin(pl->trx), &m);
	if (pl->try != 0)
		rotation_y(cos(pl->try), sin(pl->try), &m);
	if (pl->trz != 0)
		rotation_z(cos(pl->trz), sin(pl->trz), &m);
	if (pl->trx != 0 || pl->try != 0 || pl->trz != 0)
		multiply_matrices(&m, transform_m, transform_m);
}

void	make_plane(t_plane_info *pl, t_shape *obj)
{
	t_vector	vec_default;
	t_matrix	rotation_m;
	t_matrix	translation_m;
	t_matrix	transform_m;

	new_plane(obj);
	obj->cast_shadow = pl->cast_shadow;
	obj->material.color = pl->color;
	new_vector(0, 1, 0, &vec_default);
	calculate_rotation_matrix(&vec_default, &pl->normal, &rotation_m);
	get_identity_matrix(&transform_m);
	set_rotations(pl, &transform_m);
	multiply_matrices(&transform_m, &rotation_m, &rotation_m);
	translation(pl->center.x, pl->center.y, pl->center.z, &translation_m);
	multiply_matrices(&translation_m, &rotation_m, &transform_m);
	set_transform(obj, &transform_m);
}

static bool	pl_info_2(t_line_parse_env *env, t_plane_info *pl)
{
	char	**rgb;
	char	**point;
	char	**normal;

	env->error_type = RGB;
	rgb = ft_subsplit(env->line[3], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (false);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255,
		ft_atof(rgb[2]) / 255, &pl->color);
	env->error_type = NORMAL_;
	normal = ft_subsplit(env->line[2], ",\n");
	if (triplets(normal, -1, 1, env))
		return (free_s(rgb), false);
	new_vector(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]),
		&pl->normal);
	point = ft_subsplit(env->line[1], ",\n");
	env->error_type = POINT;
	if (triplets(point, (double)INT_MIN, (double)INT_MAX, env))
		return (free_s(normal), free_s(rgb), false);
	new_point(ft_atof(point[0]), ft_atof(point[1]),
		ft_atof(point[2]), &pl->center);
	return (free_s(normal), free_s(rgb), free_s(point), true);
}

static bool	pl_info_1(t_line_parse_env *env, t_plane_info *pl, int *len)
{
	int	i;

	pl->trx = 0;
	pl->try = 0;
	pl->trz = 0;
	pl->material = false;
	if (*len >= 6)
	{
		i = 4;
		while (env->line[++i])
		{
			if (ft_strncmp(env->line[i], "Trx", 4) == 0)
				pl->trx = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Try", 4) == 0)
				pl->try = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Trz", 4) == 0)
				pl->trz = ft_atof(env->line[++i]);
			else if ((i == 5 && i == *len - 1) || (i == *len - 1
					&& (pl->trx != 0 || pl->try != 0 || pl->trz != 0)))
				pl->material = true;
			else
				return (false);
		}
	}
	return (true);
}

int	init_plane(t_line_parse_env *env, t_shape *obj)
{
	t_plane_info	pl;
	int				len;

	len = ft_strarr_len(env->line);
	if (!pl_info_1(env, &pl, &len) || len < 5)
		return (file_error(env, ERR_PLANE));
	if (!pl_info_2(env, &pl))
		return (1);
	env->error_type = SHADOWS;
	if (solo(env->line[4], 0, 1, env))
		return (1);
	pl.cast_shadow = ft_atoi(env->line[4]);
	make_plane(&pl, obj);
	obj->cast_shadow = 1;
	if (env->line[4])
		obj->cast_shadow = ft_atoi(env->line[4]);
	if (pl.material && find_material(env->material, obj, env->line[len - 1], env))
		return (1);
	return (0);
}
