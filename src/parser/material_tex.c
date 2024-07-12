#include "parser.h"

int mat_tex(t_material *material, int *index, t_line_parse_env	*env)
{
    char *texture_path;
   // int length;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
    texture_path = env->line[*index];
    // length = ft_strlen(texture_path);
    new_texture_map(&material->pattern, texture_path);
    return (0);
}