#include "parser.h"

int	mat_color(t_material *material, int *index, t_line_parse_env	*env)
{
	char	**rgb;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[*index], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255, ft_atof(rgb[2]) / 255, &material->color);
	free_s(rgb);
	return (0);
}

int	mat_ambient(t_material *material, int *index, t_line_parse_env	*env)
{
	char	**rgb;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[*index], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	new_color(ft_atof(rgb[0]) / 255, ft_atof(rgb[1]) / 255, ft_atof(rgb[2]) / 255, &material->ambient);
	free_s(rgb);
	return (0);
}

int	mat_diffuse(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = DIF_VALID;
	if (solo(env->line[*index], 0, 1, env))
		return (1);
	material->diffuse = ft_atof(env->line[*index]);
	return (0);
}

int	mat_specular(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = SPEC_VALID;
	if (solo(env->line[*index], 0, 1, env))
		return (1);
	material->specular = ft_atof(env->line[*index]);
	return (0);
}

int	mat_shininess(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = SHINE_VALID;
	if (solo(env->line[*index], 0, 128, env))
		return (1);
	material->shininess = ft_atof(env->line[*index]);
	return (0);
}

int	mat_reflectivity(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = REF_VALID;
	if (solo(env->line[*index], 0, 1, env))
		return (1);
	material->reflective = ft_atof(env->line[*index]);
	return (0);
}

int	mat_trans(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = TRANS_VALID;
	if (solo(env->line[*index], 0, 1, env))
		return (1);
	material->transparency = ft_atof(env->line[*index]);
	return (0);
}

int	mat_refractive(t_material *material, int *index, t_line_parse_env	*env)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
	env->error_type = RIF_VALID;
	if (solo(env->line[*index], 1, 2.5, env))
		return (1);
	material->refractive_index = ft_atof(env->line[*index]);
	return (0);
}