/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_II.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:53:26 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/03 14:53:27 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	mat_specular(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = SPEC_VALID;
	if (solo(env->line[*index], 0, 1, env))
		return (1);
	material->specular = ft_atof(env->line[*index]);
	return (0);
}

int	mat_shininess(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = SHINE_VALID;
	if (solo(env->line[*index], 0, 128, env))
		return (1);
	material->shininess = ft_atof(env->line[*index]);
	return (0);
}

int	mat_reflect(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = REF_VALID;
	if (solo(env->line[*index], 0, 1, env))
		return (1);
	material->reflective = ft_atof(env->line[*index]);
	return (0);
}

int	mat_trans(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = TRANS_VALID;
	if (solo(env->line[*index], 0, 1, env))
		return (1);
	material->transparency = ft_atof(env->line[*index]);
	return (0);
}

int	mat_refractive(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = RIF_VALID;
	if (solo(env->line[*index], 1, 2.5, env))
		return (1);
	material->refractive_index = ft_atof(env->line[*index]);
	return (0);
}
