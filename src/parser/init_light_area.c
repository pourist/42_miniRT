/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_area.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:58:12 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/12 15:58:14 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	create_area_light(t_light *light, char **rgb, char **pos,
		t_alight_params *lp)
{
	new_point(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]), &lp->corner);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255,
		ft_atof(rgb[2]) / 255, &lp->intensity);
	new_area_light(lp, light);
}

static bool	set_area_light_params(t_alight_params *lp, t_line_parse_env *env)
{
	env->error_type = UV_VEC;
	if (solo(env->line[2], (double)INT_MIN, (double)INT_MAX, env)
		&& solo(env->line[3], (double)INT_MIN, (double)INT_MAX, env))
		return (false);
	env->error_type = UV_STEPS;
	if (solo(env->line[4], 0, INT_MAX, env)
		&& solo(env->line[5], 0, INT_MAX, env))
		return (false);
	new_vector(ft_atof(env->line[2]), 0, 0, &lp->full_uvec);
	new_vector(0, ft_atof(env->line[3]), 0, &lp->full_vvec);
	lp->usteps = ft_atoi(env->line[4]);
	lp->vsteps = ft_atoi(env->line[5]);
	return (true);
}

int	init_area_light(t_line_parse_env *env, t_light *light)
{
	char			**rgb;
	char			**pos;
	t_alight_params	lp;

	rgb = NULL;
	pos = NULL;
	if (ft_strarr_len(env->line) != 7)
		return (file_error(env, ERR_AREA_LIGHT));
	env->error_type = POS;
	pos = ft_subsplit(env->line[1], ",\n");
	if (triplets(pos, (double)INT_MIN, (double)INT_MAX, env))
		return (free_s(pos), 1);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[6], ",\n");
	if (triplets(rgb, 0, INT_MAX, env))
		return (free_s(pos), free_s(rgb), 1);
	if (!set_area_light_params(&lp, env))
		return (free_s(pos), free_s(rgb), 1);
	create_area_light(light, rgb, pos, &lp);
	free_s(rgb);
	free_s(pos);
	return (0);
}
