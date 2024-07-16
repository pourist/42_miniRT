#include "parser.h"

int	pat_type(char *line, int *i, t_line_parse_env *env, 
		t_pattern **pattern)
{
	int	j;

	j = *i;
	if (!ft_strncmp(line, "texture", 8) && pat_text(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "cubed_texture", 14) && cub_text(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "blended", 14) && p_blended(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "checkers", 14) && p_checkers(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "full_gradient", 14) && p_f_grad(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "gradient", 14) && p_grad(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "radial", 14) && p_radial(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "ring", 14) && p_ring(*pattern, i, env))
		return (1);
	else if (!ft_strncmp(line, "strip", 14) && p_strip(*pattern, i, env))
		return (1);
	else if (j == *i)
		return (file_error_line(env->line_number, "pattern error"));
	return ((*i)++, 0);
}

int	init_pattern(t_line_parse_env	*env, t_pattern **pattern)
{
	int i;

	i = 2;
	if (ft_strarr_len(env->line) < 2)
		return (file_error_line(env->line_number, ERR_PAT), 1);
	*pattern = (t_pattern *)malloc(sizeof(t_pattern));
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

void	parse_init_pat(t_line_parse_env	*parse, int *index, t_e_counts *count)
{
	parse->line_number = 1;
	*index = 0;
	count->pat = (t_pattern **)ft_calloc(count->pattern + 1, 
		sizeof(t_pattern*));
}

int	read_pattern(t_e_counts *count, char *file)
{
	t_line_parse_env	parse;
	int		index;

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
		if (!ft_strncmp(parse.line[0], "pattern", 8) && parse.line[0])
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
