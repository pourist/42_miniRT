#include "parser.h"

int mat_tex(t_material *material, int *index, t_line_parse_env	*env)
{
    char *texture_path;
    int length;

	(*index)++;
	if (!env->line[*index] || env->line[*index][0] == '\n')
		return (file_error_line(env->line_number, ERR_MAT));
    texture_path = env->line[*index];
    length = ft_strlen(texture_path);
    if (length >= 6 && texture_path[0] == '"' && 
        texture_path[length - 1] == '"' &&
            ft_strncmp(&texture_path[length - 5], ".png\"", 5) == 0) 
        new_texture_map(&material->pattern, texture_path);
    else
        return (file_error_line(env->line_number, ERR_TEX_FORMAT));
    return (0);
}