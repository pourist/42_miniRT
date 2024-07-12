/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_area_spot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:00:07 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/12 16:00:21 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	set_area_spotlight_params(t_aspotlight_params *asp, char **pos,
		char **to, t_line_parse_env *env)
{
	t_point	to_point; 

	env->error_type = POS;
	pos = ft_subsplit(env->line[1], ",\n");
	if (triplets(pos, (double)INT_MIN, (double)INT_MAX, env))
		return (false);
	to = ft_subsplit(env->line[2], ",\n");
	if (triplets(to, (double)INT_MIN, (double)INT_MAX, env))
		return (false);
	new_point(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]), &asp->corner);
	new_point(ft_atof(to[0]), ft_atof(to[1]), ft_atof(to[2]), &to_point);
	subtract(&to_point, &asp->corner, &asp->direction);
	return (true);
}

static bool	set_area_spotlight_params2(t_aspotlight_params *asp, char **rgb,
		t_line_parse_env *env)
{
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[9], ",\n");
	if (triplets(rgb, 0, INT_MAX, env))
		return (false);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255,
		ft_atof(rgb[2]) / 255, &asp->intensity);
	return (true);
}

static bool	set_area_spotlight_params3(t_aspotlight_params *asp,
		t_line_parse_env *env)
{
	env->error_type = UV_VEC;
	if (solo(env->line[3], (double)INT_MIN, (double)INT_MAX, env)
		&& solo(env->line[4], (double)INT_MIN, (double)INT_MAX, env))
		return (false);
	new_vector(ft_atof(env->line[2]), 0, 0, &asp->full_uvec);
	new_vector(0, ft_atof(env->line[3]), 0, &asp->full_vvec);
	env->error_type = UV_STEPS;
	if (solo(env->line[5], 0, INT_MAX, env)
		&& solo(env->line[6], 0, INT_MAX, env))
		return (false);
	asp->usteps = ft_atoi(env->line[4]);
	asp->vsteps = ft_atoi(env->line[5]);
	env->error_type = SPOTLIGHT_CRADIAN;
	if (solo(env->line[7], 0, (double)INT_MAX, env))
		return (false);
	asp->center_radian = ft_atof(env->line[3]);
	env->error_type = SPOTLIGHT_FRADIAN;
	if (solo(env->line[8], 0, (double)INT_MAX, env))
		return (false);
	asp->fade_radian = ft_atof(env->line[4]);
	return (true);
}

int	init_area_spotlight(t_line_parse_env *env, t_light *light)
{
	char				**rgb;
	char				**pos;
	char				**to;
	t_aspotlight_params	asp;

	pos = NULL;
	to = NULL;
	rgb = NULL;
	if (ft_strarr_len(env->line) != 10)
		return (file_error(env, ERR_AREA_SPOTLIGHT));
	if (!set_area_spotlight_params(&asp, pos, to, env))
		return (free_s(pos), free_s(to), free_s(rgb), 1);
	if (!set_area_spotlight_params2(&asp, rgb, env))
		return (free_s(pos), free_s(to), free_s(rgb), 1);
	if (!set_area_spotlight_params3(&asp, env))
		return (free_s(pos), free_s(to), free_s(rgb), 1);
	new_area_spotlight(&asp, light);
	free_s(pos);
	free_s(to);
	free_s(rgb);
	return (0);
}
