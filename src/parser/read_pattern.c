/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pattern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:30:06 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/17 17:11:37 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	transform_type(char *line, int *i, t_line_parse_env *env,
		t_pattern **pattern)
{
	int	j;

	j = *i;
	if (!ft_strncmp(line, "Tt", 3) && transform_tt(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "Ts", 3) && transform_ts(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "Trx", 4) && transform_trx(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "Try", 4) && transform_try(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "Trz", 4) && transform_trz(*pattern, i, env))
		return (1);
	else if (j == *i)
		return (file_error_line(env->line_number, "pattern error"));
	return ((*i)++, 0);
}

static int	pat_type(char *line, int *i, t_line_parse_env *env,
		t_pattern **p)
{
	int	j;

	j = *i;
	if (!ft_strncmp(line, "texture", 8) && pat_text(*p, i, env))
		return (1);
	else if (!ft_strncmp(line, "cubed_texture", 14) && cub_text(*p, i, env))
		return (1);
	else if (!ft_strncmp(line, "blended", 14) && p_blended(*p, i, env))
		return (1);
	else if (!ft_strncmp(line, "checkers", 14) && p_checkers(*p, i, env))
		return (1);
	else if (!ft_strncmp(line, "full_gradient", 14) && p_f_grad(*p, i, env))
		return (1);
	else if (!ft_strncmp(line, "gradient", 14) && p_grad(*p, i, env))
		return (1);
	else if (!ft_strncmp(line, "radial", 14) && p_radial(*p, i, env))
		return (1);
	else if (!ft_strncmp(line, "ring", 14) && p_ring(*p, i, env))
		return (1);
	else if (!ft_strncmp(line, "strip", 14) && p_strip(*p, i, env))
		return (1);
	else if (j == *i)
		return (file_error_line(env->line_number, "pattern error"));
	return ((*i)++, 0);
}

static int	init_pattern(t_line_parse_env	*env, t_pattern **pattern)
{
	int	i;

	i = 2;
	if (ft_strarr_len(env->line) < 2)
		return (file_error_line(env->line_number, ERR_PAT), 1);
	*pattern = (t_pattern *)ft_calloc(1, sizeof(t_pattern));
	new_pattern(*pattern);
	(*pattern)->name = ft_strdup(env->line[1]);
	if (env->line[2] && pat_type(env->line[2], &i, env, pattern))
		return (1);
	while (env->line[i])
	{
		if (transform_type(env->line[i], &i, env, pattern))
			return (1);
	}
	return (0);
}

static void	parse_init_pat(t_line_parse_env	*parse, int *index,
		t_e_counts *count)
{
	parse->line_number = 1;
	*index = 0;
	count->pat = (t_pattern **)ft_calloc(count->pattern + 1,
			sizeof(t_pattern*));
}

int	read_pattern(t_e_counts *count, char *file)
{
	t_line_parse_env	parse;
	int					index;

	parse_init_pat(&parse, &index, count);
	while (1)
	{
		parse.temp = get_next_line(count->fd);
		if (!parse.temp || parse.temp[0] == '\0')
		{
			free(parse.temp);
			break ;
		}
		parse.line = ft_subsplit (parse.temp, " \t\n");
		free(parse.temp);
		if (parse.line[0] && !ft_strncmp(parse.line[0], "pattern", 8))
		{
			if (init_pattern(&parse, &count->pat[index]))
				return (free_s(parse.line), 1);
			index++;
		}
		parse.line_number++;
		free_s(parse.line);
	}
	return (reset_file(count, file), 0);
}
