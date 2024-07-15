#include "parser.h"

int transform_tt(t_pattern *pattern, int *index, t_line_parse_env *env)
{
    char    **tripple;

    (*index)++;
    if (!env->line[*index] || env->line[*index][0] == '\n')
        return (file_error_line(env->line_number, ERR_PAT));
    env->error_type = E_TRIPPLE;
	tripple = ft_subsplit(env->line[*index], ",\n");
	if (triplets(tripple, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
    (void)pattern;
    return(free_s(tripple), 0);
}

int transform_ts(t_pattern *pattern, int *index, t_line_parse_env *env)
{
    char    **tripple;

    (*index)++;
    if (!env->line[*index] || env->line[*index][0] == '\n')
        return (file_error_line(env->line_number, ERR_PAT));
    env->error_type = E_TRIPPLE;
	tripple = ft_subsplit(env->line[*index], ",\n");
	if (triplets(tripple, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
    (void)pattern;
    return(free_s(tripple), 0);
}

int transform_trx(t_pattern *pattern, int *index, t_line_parse_env *env)
{
    char    **tripple;

    (*index)++;
    if (!env->line[*index] || env->line[*index][0] == '\n')
        return (file_error_line(env->line_number, ERR_PAT));
    env->error_type = E_DOUBLE_I;
	if (triplets(tripple, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
    (void)pattern;
    return(free_s(tripple), 0);
}

int transform_type(char *line, int *i, t_line_parse_env *env, 
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