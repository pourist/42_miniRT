/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:44:57 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/12 15:59:54 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	create_light(char **rgb, double ratio, char **pos, t_light *light)
{
	double	r;
	double	g;
	double	b;

	r = (ft_atof(rgb[0]) / 255) * ratio;
	g = (ft_atof(rgb[1]) / 255) * ratio;
	b = (ft_atof(rgb[2]) / 255) * ratio;
	new_color(r, g, b, &light->intensity);
	new_point(
		ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]), &light->position);
	free_s(rgb);
	free_s(pos);
}

int	init_light(t_line_parse_env *env, t_light *light)
{
	char	**rgb;
	char	**pos;

	rgb = NULL;
	pos = NULL;
	if (ft_strarr_len(env->line) != 4)
		return (file_error(env, ERR_LIGHT));
	env->error_type = L_RATIO;
	if (solo(env->line[2], 0, 1, env))
		return (1);
	env->error_type = POS;
	pos = ft_subsplit(env->line[1], ",\n");
	if (triplets(pos, (double)INT_MIN, (double)INT_MAX, env))
		return (free_s(pos), 1);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[3], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (free_s(pos), free_s(rgb), 1);
	create_light(rgb, ft_atof(env->line[2]), pos, light);
	return (0);
}
