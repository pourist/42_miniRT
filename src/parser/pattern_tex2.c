/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_tex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:29:59 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/24 19:15:26 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	p_f_grad(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char		**rgb1;
	char		**rgb2;
	t_color		colors[2];
	t_pattern	tmp[2];

	rgb1 = NULL;
	rgb2 = NULL;
	if (pattern_type_parser(index, env, &rgb1, &rgb2))
		return (1);
	new_color(ft_atof(rgb1[0]) / 255, ft_atof(rgb1[1]) / 255,
		ft_atof(rgb1[2]) / 255, &colors[0]);
	new_color(ft_atof(rgb2[0]) / 255, ft_atof(rgb2[1]) / 255,
		ft_atof(rgb2[2]) / 255, &colors[1]);
	new_full_gradient_pattern(new_solid_pattern(&colors[0], &tmp[0]),
		new_solid_pattern(&colors[1], &tmp[1]), pattern);
	return (free_s(rgb1), free_s(rgb2), 0);
}

int	p_grad(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char		**rgb1;
	char		**rgb2;
	t_color		colors[2];
	t_pattern	tmp[2];

	rgb1 = NULL;
	rgb2 = NULL;
	if (pattern_type_parser(index, env, &rgb1, &rgb2))
		return (1);
	new_color(ft_atof(rgb1[0]) / 255, ft_atof(rgb1[1]) / 255,
		ft_atof(rgb1[2]) / 255, &colors[0]);
	new_color(ft_atof(rgb2[0]) / 255, ft_atof(rgb2[1]) / 255,
		ft_atof(rgb2[2]) / 255, &colors[1]);
	new_gradient_pattern(new_solid_pattern(&colors[0], &tmp[0]),
		new_solid_pattern(&colors[1], &tmp[1]), pattern);
	return (free_s(rgb1), free_s(rgb2), 0);
}

int	p_radial(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char		**rgb1;
	char		**rgb2;
	t_color		colors[2];
	t_pattern	tmp[2];

	rgb1 = NULL;
	rgb2 = NULL;
	if (pattern_type_parser(index, env, &rgb1, &rgb2))
		return (1);
	new_color(ft_atof(rgb1[0]) / 255, ft_atof(rgb1[1]) / 255,
		ft_atof(rgb1[2]) / 255, &colors[0]);
	new_color(ft_atof(rgb2[0]) / 255, ft_atof(rgb2[1]) / 255,
		ft_atof(rgb2[2]) / 255, &colors[1]);
	new_radial_gradient_pattern(new_solid_pattern(&colors[0], &tmp[0]),
		new_solid_pattern(&colors[1], &tmp[1]), pattern);
	return (free_s(rgb1), free_s(rgb2), 0);
}

int	p_ring(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char		**rgb1;
	char		**rgb2;
	t_color		colors[2];
	t_pattern	tmp[2];

	rgb1 = NULL;
	rgb2 = NULL;
	if (pattern_type_parser(index, env, &rgb1, &rgb2))
		return (1);
	new_color(ft_atof(rgb1[0]) / 255, ft_atof(rgb1[1]) / 255,
		ft_atof(rgb1[2]) / 255, &colors[0]);
	new_color(ft_atof(rgb2[0]) / 255, ft_atof(rgb2[1]) / 255,
		ft_atof(rgb2[2]) / 255, &colors[1]);
	new_radial_gradient_pattern(new_solid_pattern(&colors[0], &tmp[0]),
		new_solid_pattern(&colors[1], &tmp[1]), pattern);
	return (free_s(rgb1), free_s(rgb2), 0);
}

int	p_strip(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char		**rgb1;
	char		**rgb2;
	t_color		colors[2];
	t_pattern	tmp[2];

	rgb1 = NULL;
	rgb2 = NULL;
	if (pattern_type_parser(index, env, &rgb1, &rgb2))
		return (1);
	new_color(ft_atof(rgb1[0]) / 255, ft_atof(rgb1[1]) / 255,
		ft_atof(rgb1[2]) / 255, &colors[0]);
	new_color(ft_atof(rgb2[0]) / 255, ft_atof(rgb2[1]) / 255,
		ft_atof(rgb2[2]) / 255, &colors[1]);
	new_stripe_pattern(new_solid_pattern(&colors[0], &tmp[0]),
		new_solid_pattern(&colors[1], &tmp[1]), pattern);
	return (free_s(rgb1), free_s(rgb2), 0);
}
