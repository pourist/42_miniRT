#include "parser.h"


int pat_text(t_pattern *pattern, int *index, t_line_parse_env *env)
{
    char *texture_path;
    int length;

    (*index)++;
    if (!env->line[*index] || env->line[*index][0] == '\n')
        return (file_error_line(env->line_number, ERR_TEX_FORMAT));
    texture_path = env->line[*index];
    length = ft_strlen(texture_path);
    if (length >= 4 && ft_strncmp(texture_path + length - 4, ".png", 5) == 0)
        new_texture_map(pattern, texture_path);
    else{
        return (file_error_line(env->line_number, ERR_TEX_FORMAT));}
    return (0);
}

int cub_text(t_pattern *pattern, int *index, t_line_parse_env *env)
{
    int length;
    char const	*paths[6];
    int j;

    j = 0;
    (*index)++;
    while (j < 6)
    {
        if (!env->line[*index] || env->line[*index][0] == '\n')
            return (file_error_line(env->line_number, ERR_CUBE_TEX));
        length = ft_strlen(env->line[*index]);
        if (!(length >= 4 && !ft_strncmp(env->line[*index] + length - 4, ".png", 5)))
            return (file_error_line(env->line_number, ERR_CUBE_TEX));
        paths[j] = env->line[*index];
        (*index)++;
        j++;
    }
    new_cubic_texture_map(pattern, paths);
    return (0);
}

int pat_type(char *line, int *i, t_line_parse_env *env, 
		t_pattern **pattern)
{
	int	j;

	j = *i;
    if (!ft_strncmp(line, "texture", 8) && pat_text(*pattern, i, env))
		return (1);
    else if (!ft_strncmp(line, "cubed_texture", 14) && cub_text(*pattern, i, env))
		return (1);
	else if (j == *i)
		return (file_error_line(env->line_number, "pattern error"));
	return (0);
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
	{
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