/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:11:45 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/03 16:11:51 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	make_plane(char **rgb, char **normal, char **center, t_shape *obj)
{
	t_vector	vec_default;
	t_vector	vec_user;
	t_matrix	rotation_m;
	t_matrix	translation_m;
	t_matrix	transform_m;

	new_plane(obj);
	new_color(atof(rgb[0]) * INV_255, atof(rgb[1]) * INV_255,
		atof(rgb[2]) * INV_255, &obj->material.color);
	new_vector(0, 1, 0, &vec_default);
	new_vector(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]),
		&vec_user);
	calculate_rotation_matrix(&vec_default, &vec_user, &rotation_m);
	translation(atof(center[0]), atof(center[1]), atof(center[2]),
		&translation_m);
	multiply_matrices(&translation_m, &rotation_m, &transform_m);
	set_transform(obj, &transform_m);
	free_s(rgb);
	free_s(center);
	free_s(normal);
}

int	init_plane(t_line_parse_env *env, t_shape *obj)
{
	char	**rgb;
	char	**normal;
	char	**point;
	int		material;

	material = 0;
	if (ft_strarr_len(env->line) == 5)
		material = 1;
	else if (ft_strarr_len(env->line) != 4)
		return (file_error(env, ERR_PLANE));
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[3], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	env->error_type = NORMAL_;
	normal = ft_subsplit(env->line[2], ",\n");
	if (triplets(normal, -1, 1, env))
		return (free_s(rgb), 1);
	point = ft_subsplit(env->line[1], ",\n");
	env->error_type = POINT;
	if (triplets(point, (double)INT_MIN, (double)INT_MAX, env))
	{
		free_s(normal);
		return (free_s(rgb), 1);
	}
	make_plane(rgb, normal, point, obj);
	if (material && find_material(env->material, obj, env->line[4], env))
		return (1);
	return (0);
}
