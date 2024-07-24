/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_spot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:58:56 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/12 15:59:21 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	set_spotlight_params(t_spotlight_params *sp, char **pos, char **to,
		t_line_parse_env *env)
{
	t_point	to_point;

	env->error_type = POS;
	pos = ft_subsplit(env->line[1], ",\n");
	if (triplets(pos, (double)INT_MIN, (double)INT_MAX, env))
		return (false);
	to = ft_subsplit(env->line[2], ",\n");
	if (triplets(to, (double)INT_MIN, (double)INT_MAX, env))
		return (false);
	new_point(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]), &sp->position);
	new_point(ft_atof(to[0]), ft_atof(to[1]), ft_atof(to[2]), &to_point);
	subtract(&to_point, &sp->position, &sp->direction);
	return (true);
}

static bool	set_spotlight_params2(t_spotlight_params *sp, char **rgb,
		t_line_parse_env *env)
{
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[5], ",\n");
	if (triplets(rgb, 0, INT_MAX, env))
		return (false);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255,
		ft_atof(rgb[2]) / 255, &sp->intensity);
	env->error_type = SPOTLIGHT_CRADIAN;
	if (solo(env->line[3], 0, (double)INT_MAX, env))
		return (false);
	sp->center_radian = ft_atof(env->line[3]);
	env->error_type = SPOTLIGHT_FRADIAN;
	if (solo(env->line[4], 0, (double)INT_MAX, env))
		return (false);
	sp->fade_radian = ft_atof(env->line[4]);
	return (true);
}

int	init_spotlight(t_line_parse_env *env, t_light *light)
{
	char				**rgb;
	char				**pos;
	char				**to;
	t_spotlight_params	sp;

	pos = NULL;
	to = NULL;
	rgb = NULL;
	if (ft_strarr_len(env->line) != 6)
		return (file_error(env, ERR_SPOTLIGHT));
	if (!set_spotlight_params(&sp, pos, to, env))
		return (free_s(pos), free_s(to), free_s(rgb), 1);
	if (!set_spotlight_params2(&sp, rgb, env))
		return (free_s(pos), free_s(to), free_s(rgb), 1);
	new_spotlight(&sp, light);
	free_s(pos);
	free_s(to);
	free_s(rgb);
	return (0);
}
