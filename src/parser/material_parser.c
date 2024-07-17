/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:09:21 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/11 23:15:19 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	find_material(t_material **material, t_shape *obj, char *name,
		t_line_parse_env *env)
{
	int	i;

	i = 0;
	while (material[i])
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

int	material_line_parser(char *line, int *i, t_line_parse_env *env,
		t_material **material)
{
	int	j;

	j = *i;
	if (!ft_strncmp(line, "c", 2) && mat_color(*material, i, env))
		return (1);
	else if (!ft_strncmp(line, "a", 2) && mat_ambient(*material, i, env))
		return (1);
	else if (!ft_strncmp(line, "d", 2) && mat_diffuse(*material, i, env))
		return (1);
	else if (!ft_strncmp(line, "s", 2) && mat_specular(*material, i, env))
		return (1);
	else if (!ft_strncmp(line, "sh", 3) && mat_shininess(*material, i, env))
		return (1);
	else if (!ft_strncmp(line, "refl", 5) && mat_reflect(*material, i, env))
		return (1);
	else if (!ft_strncmp(line, "trans", 6) && mat_trans(*material, i, env))
		return (1);
	else if (!ft_strncmp(line, "ri", 3) && mat_refractive(*material, i, env))
		return (1);
	else if (!ft_strncmp(line, "p", 8) && mat_pattern(*material, i, env))
		return (1);
	else if (j == *i)
		return (file_error_line(env->line_number, ERR_MAT));
	return (0);
}

int	init_material(t_line_parse_env	*env, t_material **material)
{
	int	i;

	i = 2;
	if (ft_strarr_len(env->line) < 2)
		return (file_error_line(env->line_number, ERR_MAT));
	*material = (t_material *)malloc(sizeof(t_material));
	new_material(*material);
	(*material)->name = ft_strdup(env->line[1]);
	while (env->line[i])
	{
		if (material_line_parser(env->line[i], &i, env, material))
			return (1);
		i++;
	}
	return (0);
}

void	parse_init_mat(t_line_parse_env	*parse, int *index, t_e_counts *count)
{
	parse->pat = count->pat;
	parse->line_number = 1;
	*index = 0;
	count->material = (t_material **)ft_calloc(count->mat + 1,
			sizeof(t_material*));
}

int	read_material(t_e_counts *count, char *file)
{
	t_line_parse_env	parse;
	int					index;

	parse_init_mat(&parse, &index, count);
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
		if (!ft_strncmp(parse.line[0], "material", 9) && parse.line[0])
		{
			if (init_material(&parse, &count->material[index]))
				return (free_s(parse.line), 1);
			index++;
		}
		parse.line_number++;
		free_s(parse.line);
	}
	return (reset_file(count, file), 0);
}
