/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_counter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:07:57 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/12 15:29:27 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	start_with(char *line, char *c)
{
	int	len;

	len = ft_strlen(c);
	while (*line && ft_isspace(*line))
		line++;
	if (c[0] == '\n' && !*line)
		return (1);
	if (!ft_strncmp(line, c, ft_strlen(c)))
	{
		line += len;
		if (ft_isspace(*line))
			return (1);
	}
	return (0);
}

void	counter_helper(t_e_counts *count, char *line)
{
	if (start_with(line, "A"))
		count->a_light++;
	else if (start_with(line, "C"))
		count->camera++;
	else if (start_with(line, "L"))
		count->light++;
	else if (start_with(line, "aL") || start_with(line, "sL")
		|| start_with(line, "asL"))
		count->other_light++;
	else if (start_with(line, "sp"))
		count->sphere++;
	else if (start_with(line, "cy"))
		count->cylinder++;
	else if (start_with(line, "pl"))
		count->plane++;
	else if (start_with(line, "cone"))
		count->cone++;
	else if (start_with(line, "cube"))
		count->cube++;
	else if (start_with(line, "material"))
		count->mat++;
	else if (start_with(line, ".obj"))
		count->ob++;
	else if (!start_with(line, "\n"))
		count->unknown++;
}

void	elements_counter(t_e_counts *count, char *line)
{
	while (1)
	{
		line = get_next_line(count->fd);
		if (!line || line[0] == '\0')
		{
			free(line);
			break ;
		}
		counter_helper(count, line);
		free(line);
	}
	flush_fd(count->fd);
}

int	elements_count_checker(t_e_counts *count)
{
	char	*line;

	line = NULL;
	elements_counter(count, line);
	if (count->unknown != 0)
		return (print_error(UNKNOWN_ELEMENT));
	if (count->a_light > 1)
		return (print_error(MULTI_AMBIENT));
	else if (count->a_light == 0)
		return (print_error(AMBIEN_FOUND));
	if (count->camera > 1)
		return (print_error(MULTI_CAMERA));
	else if (count->camera == 0)
		return (print_error(NO_CAMERA));
	if (count->light > 1)
		return (print_error(MULTI_LIGHT));
	else if (count->light == 0 && count->other_light == 0)
		return (print_error(NO_LIGHT));
	return (0);
}

int	init_counter_fd(t_e_counts *count, char *file)
{
	count->a_light = 0;
	count->other_light = 0;
	count->camera = 0;
	count->light = 0;
	count->sphere = 0;
	count->cylinder = 0;
	count->plane = 0;
	count->unknown = 0;
	count->cube = 0;
	count->cone = 0;
	count->mat = 0;
	count->ob = 0;
	count->fd = open(file, O_RDONLY);
	if (count->fd < 0)
		return (print_error("Error\nUnable to read the .rt file."));
	if (elements_count_checker(count))
		return (1);
	count->fd = open(file, O_RDONLY);
	return (0);
}
