#include "parser.h"

int mat_pattern(t_material *material, int *index, t_line_parse_env *env, t_patter)
{
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, "Pattern not found."));
	while (pattern[i])
	{
		if (!ft_strncmp(material[i]->name, name, ft_strlen(name)))
		{
			material[i]->pattern.texture_map.uv_mapping_fn
				= obj->material.pattern.texture_map.uv_mapping_fn;
			obj->material = *material[i];
			return (0);
		}
		i++;
	}
	return (file_error(env, MATERIAL_N));
}

int mat_cub_t(t_material *material, int *index, t_line_parse_env	*env)
{
	(void)material;
	(void)env;
	(void)index;
	return (0);
}