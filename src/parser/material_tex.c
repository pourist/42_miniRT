#include "parser.h"

int mat_pattern(t_material *material, int *index, t_line_parse_env	*env)
{
	int i;

	i = 0;
	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, "Pattern not found."));
	while (env->pat[i])
	{
		if (!ft_strncmp(env->pat[i]->name, env->line[*index], ft_strlen(env->line[*index])))
		{
			material->pattern = *env->pat[i];
			return (0);
		}
		i++;
	}
	return (file_error(env, "Pattern not found."));
}
