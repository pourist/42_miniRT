#include "parser.h"

int	init_material(t_line_parse_env	*env, t_material **material)
{
	int	i;
	int	j;

	i = 2;
    if (ft_strarr_len(env->line) < 2)
		return (file_error_line(env->line_number, ERR_MAT));
	*material = (t_material*)malloc(sizeof(t_material));
	new_material(*material);
	(*material)->name = ft_strdup(env->line[1]);
	while (env->line[i])
	{
		j = i;
		if (!ft_strncmp(env->line[i], "c", 2) && mat_color(*material, &i, env))
			return(1);
		else if (!ft_strncmp(env->line[i], "a", 2) && mat_ambient(*material, &i, env))
			return(1);
		else if (!ft_strncmp(env->line[i], "d", 2) && mat_diffuse(*material, &i, env))
			return(1);
		else if (!ft_strncmp(env->line[i], "s", 2) && mat_specular(*material, &i, env))
			return(1);
		else if (!ft_strncmp(env->line[i], "sh", 3) && mat_shininess(*material, &i, env))
			return(1);
		else if (!ft_strncmp(env->line[i], "refl", 5) && mat_reflectivity(*material, &i, env))
			return(1);
		else if (!ft_strncmp(env->line[i], "trans", 6) && mat_trans(*material, &i, env))
			return(1);
		else if (!ft_strncmp(env->line[i], "ri", 3) && mat_refractive(*material, &i, env))
			return(1);
		else if (j == i)
			return (file_error_line(env->line_number, ERR_MAT));
		i++;
	}
	(void)(material);
	return(0);
}

int	read_material(t_e_counts *count, char *file)
{
	t_line_parse_env	parse;
	int		index;

	parse.line_number = 1;
	index = 0;
	count->material = (t_material**)malloc(sizeof(t_material*) * count->mat + 1);
	count->material[count->mat] = NULL;
	while (1)
	{
		parse.temp = get_next_line(count->fd);
		if (!parse.temp || parse.temp[0] == '\0')
		{
			free(parse.temp);
			break;
		}
		parse.line = ft_subsplit (parse.temp, " \t\n");
		free(parse.temp);
		if (!ft_strncmp(parse.line[0], "material", 10) && parse.line[0])
		{
			if (init_material(&parse, &count->material[index]))
				return(free_s(parse.line), 1);
			index++;
		}
		parse.line_number++;
		free_s(parse.line);
	}
	close(count->fd);
	count->fd = open(file, O_RDONLY);
	return(0);
}