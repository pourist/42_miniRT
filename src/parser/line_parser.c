/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:10:46 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/03 16:11:32 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_type(t_line_parse_env *parse)
{
	if (parse->line[0] == NULL)
		parse->type = EMPTY_LINE;
	else if (!ft_strncmp(parse->line[0], "A", 2) && parse->line[0])
		parse->type = AMBIENT;
	else if (!ft_strncmp(parse->line[0], "C", 2) && parse->line[0])
		parse->type = CAMERA;
	else if (!ft_strncmp(parse->line[0], "L", 2) && parse->line[0])
		parse->type = LIGHT;
	else if (!ft_strncmp(parse->line[0], "sp", 3) && parse->line[0])
		parse->type = SPHERE;
	else if (!ft_strncmp(parse->line[0], "cy", 3) && parse->line[0])
		parse->type = CYLINDER;
	else if (!ft_strncmp(parse->line[0], "pl", 3) && parse->line[0])
		parse->type = PLANE;
	else if (!ft_strncmp(parse->line[0], "cone", 5) && parse->line[0])
		parse->type = CONE;
	else if (!ft_strncmp(parse->line[0], "cube", 5) && parse->line[0])
		parse->type = CUBE;
	else if (!ft_strncmp(parse->line[0], ".obj", 5) && parse->line[0])
		parse->type = OBJ;
	else
		parse->type = MATERIAL;
}

int	parse_line(int fd, t_line_parse_env *parse)
{
	parse->line_number++;
	parse->temp = get_next_line(fd);
	if (!parse->temp || parse->temp[0] == '\0')
	{
		free(parse->temp);
		return (1);
	}
	parse->line = ft_subsplit (parse->temp, " \t\n");
	free(parse->temp);
	set_type(parse);
	return (0);
}

int	read_lines_init(t_world *world, t_mini_rt *minirt, t_e_counts *count)
{
	t_line_parse_env	parse;
	int					i;
	int					obj;

	parse.material = count->material;
	parse.line_number = 0;
	i = 0;
	obj = 0;
	while (1)
	{
		if (parse_line(count->fd, &parse))
			break ;
		if (parse.type == AMBIENT && init_ambient(&parse, world))
			return (free_s(parse.line));
		if (parse.type == CAMERA && init_camera(&parse, &(minirt->camera)))
			return (free_s(parse.line));
		if (parse.type == LIGHT && init_light(&parse, &(world->lights[i++])))
			return (free_s(parse.line));
		if (parse.type == SPHERE && init_sphere(&parse, &(world->objs[obj++])))
			return (free_s(parse.line));
		if (parse.type == PLANE && init_plane(&parse, &(world->objs[obj++])))
			return (free_s(parse.line));
		if (parse.type == CYLINDER && init_cylinder(&parse, &(world->objs[obj++])))
			return (free_s(parse.line));
		if (parse.type == CONE && init_cone(&parse, &(world->objs[obj++])))
			return (free_s(parse.line));
		if (parse.type == CUBE && init_cube(&parse, &(world->objs[obj++])))
			return (free_s(parse.line));
		if (parse.type == OBJ && init_obj(&parse, &(world->objs[obj++])))
			return (free_s(parse.line));
		free_s(parse.line);
	}
	return (0);
}
