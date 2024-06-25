#include "parser.h"

int	start_with(char	*line, char *c)
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
		if (start_with(line, "A"))
			count->a_light++;
		else if (start_with(line, "C"))
			count->camera++;
		else if (start_with(line, "L"))
			count->light++;
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
		else if (!start_with(line, "\n"))
			count->unknown++;
		free(line);
	}
	close(count->fd);
}

int	elements_count_checker(t_e_counts *count)
{
	char	*line;

	line = NULL;
	elements_counter(count, line);
	if (count->unknown != 0)
		return (print_error("Error\nUnknown element found."));
	if (count->a_light > 1)
		return (print_error("Error\nMultiple instances of Ambient Lighting found."));
	else if (count->a_light == 0)
		return (print_error("Error\nNo Ambient Lighting found."));
	if (count->camera > 1)
		return (print_error("Error\nMultiple instances of Camera found."));
	else if (count->camera == 0)
		return (print_error("Error\nNo Camera found."));
	if (count->light > 1)
		return (print_error("Error\nMultiple instances of Light found."));
	else if (count->light == 0)
		return (print_error("Error\nNo Light found."));
	return (0);
}

int	init_counter_fd(t_e_counts *count, char *file)
{
	count->a_light = 0;
	count->camera = 0;
	count->light = 0;
	count->sphere = 0;
	count->cylinder = 0;
	count->plane = 0;
	count->unknown = 0;
	count->cube = 0;
	count->cone = 0;
	count->fd = open(file, O_RDONLY);
	if (count->fd < 0)
		return (print_error("Error\nUnable to read the .rt file."));
	if (elements_count_checker(count))
		return (1);
	count->fd = open(file, O_RDONLY);
	return (0);
}
