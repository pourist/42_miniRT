/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:51:52 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/24 10:43:34 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	mat_color(t_material *material, int *index, t_line_parse_env	*env)
{
	char	**rgb;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[*index], ",\n");
	if (triplets(rgb, 0, INT_MAX, env))
		return (1);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255, ft_atof(rgb[2])
		/ 255, &material->color);
	free_s(rgb);
	return (0);
}

int	mat_ambient(t_material *material, int *index, t_line_parse_env	*env)
{
	char	**rgb;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[*index], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255, ft_atof(rgb[2])
		/ 255, &material->ambient);
	free_s(rgb);
	return (0);
}

int	mat_diffuse(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = DIF_VALID;
	if (solo(env->line[*index], 0, 1, env))
		return (1);
	material->diffuse = ft_atof(env->line[*index]);
	return (0);
}
