#include "parser.h"

int	pat_text(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char	*texture_path;
	int		length;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_TEX_FORMAT));
	texture_path = env->line[*index];
	length = ft_strlen(texture_path);
	if (length >= 4 && ft_strncmp(texture_path + length - 4, ".png", 5) == 0)
		new_texture_map(pattern, texture_path);
	else
		return (file_error_line(env->line_number, ERR_TEX_FORMAT));
	return (0);
}

int	cub_text(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	int			length;
	char const	*paths[6];
	int			j;

	j = 0;
	(*index)++;
	while (j < 6)
	{
		if (!env->line[*index] || env->line[*index][0] == '\n')
			return (file_error_line(env->line_number, ERR_CUBE_TEX));
		length = ft_strlen(env->line[*index]);
		if (!(length >= 4 && !ft_strncmp(env->line[*index]
					+ length - 4, ".png", 5)))
			return (file_error_line(env->line_number, ERR_CUBE_TEX));
		paths[j] = env->line[*index];
		(*index)++;
		j++;
	}
	new_cubic_texture_map(pattern, paths);
	return (0);
}

int	patter_type_parser(int *index, t_line_parse_env *env,
		char **rgb1, char **rgb2)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, RGB_INVALID));
	env->error_type = RGB;
	rgb1 = ft_subsplit(env->line[*index], ",\n");
	if (triplets(rgb1, 0, 255, env))
		return (1);
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, RGB_INVALID));
	env->error_type = RGB;
	rgb2 = ft_subsplit(env->line[*index], ",\n");
	if (triplets(rgb2, 0, 255, env))
		return (free_s(rgb1), 1);
	return (0);
}

int	p_blended(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char	**rgb1;
	char	**rgb2;

	rgb1 = NULL;
	rgb2 = NULL;
	if (patter_type_parser(index, env, rgb1, rgb2))
		return (1);
	(void)pattern;
	return (free_s(rgb1), free_s(rgb2), 0);
}

int	p_checkers(t_pattern *pattern, int *index, t_line_parse_env *env)
{
	char	**rgb1;
	char	**rgb2;

	rgb1 = NULL;
	rgb2 = NULL;
	if (patter_type_parser(index, env, rgb1, rgb2))
		return (1);
	(void)pattern;
	return (free_s(rgb1), free_s(rgb2), 0);
}
