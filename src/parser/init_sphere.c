/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:13:52 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/17 16:31:50 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	make_sphere(char **rgb, double diam, char **center, t_shape *obj)
{
	t_matrix	m1;
	t_matrix	m2;
	t_matrix	final;
	double		rgb_d[3];

	rgb_d[0] = (ft_atof(rgb[0]) / 255);
	rgb_d[1] = (ft_atof(rgb[1]) / 255);
	rgb_d[2] = (ft_atof(rgb[2]) / 255);
	new_sphere(obj);
	new_color(rgb_d[0], rgb_d[1], rgb_d[2], &obj->material.color);
	translation(ft_atof(center[0]), ft_atof(center[1]),
		ft_atof(center[2]), &m1);
	scaling(diam * 0.5, diam * 0.5, diam * 0.5, &m2);
	multiply_matrices(&m1, &m2, &final);
	set_transform(obj, &final);
	free_s(rgb);
	free_s(center);
}

int	init_sphere(t_line_parse_env *env, t_shape *obj)
{
	char	**center;
	char	**rgb;
	int		material;

	material = has_material(env, 5);
	if (!material && ft_strarr_len(env->line) != 4)
		return (file_error(env, ERR_SPHERE));
	env->error_type = DIAM;
	if (solo(env->line[2], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[3], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (free_s(center), 1);
	make_sphere(rgb, ft_atof(env->line[2]), center, obj);
	if (material && find_material(env->material, obj, env->line[4], env))
		return (1);
	return (0);
}
