#include "parser.h"

int	p_f_grad(t_pattern *pattern, int *index, t_line_parse_env *env)
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

int	p_grad(t_pattern *pattern, int *index, t_line_parse_env *env)
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

int	p_radial(t_pattern *pattern, int *index, t_line_parse_env *env)
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

int	p_ring(t_pattern *pattern, int *index, t_line_parse_env *env)
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

int	p_strip(t_pattern *pattern, int *index, t_line_parse_env *env)
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
