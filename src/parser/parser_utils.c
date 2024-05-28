#include "parser.h"

int ft_strarr_len(char **line)
{
    int count;
	
	count = 0;
    while (line[count] != NULL)
    {
        count++;
    }
    return (count);
}

int	print_error(char	*text)
{
	write(1, text, ft_strlen(text));
    write(1, "\n", 1);
	return (1);
}

int	free_print_error(t_world *minirt, char *str)
{
	free_world(minirt);
	return(print_error(str));
}

int	free_s(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (1);
}

int	start_with(char	*line, char *c)
{
	int	len;

	len = ft_strlen(c);
	while (*line && ft_isspace(*line))
		line++;
	if (!ft_strncmp(line, c, ft_strlen(c)))
	{
		line += len;
		if (ft_isspace(*line))
			return (1);
	}
	return (0);
}

void	elements_counter(t_e_counts *count, int fd, char *line)
{
    while (1)
	{
		line = get_next_line(fd);
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
		else
			count->unknown++;
		free(line);
	}
	close(fd);
}

int elements_count_checker(t_e_counts *count, int fd)
{
    char    *line;

	line = NULL;
	count->a_light = 0;
	count->camera = 0;
	count->light = 0;
	count->sphere = 0;
	count->cylinder = 0;
	count->plane = 0;
	count->unknown = 0;
    elements_counter(count, fd, line);
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

int	is_valid_number(char *str)
{
	int	point;
	int	i;
	char *temp;
	
	temp = str;
	i = 0;
	point = 0;
	if (*temp == '+' || *temp == '-')
		temp++;
	while (*temp)
	{
		if (ft_isdigit(*temp))
			i = 1;
		else if (*temp == '.' && !point && i)
			point = 1;
		else
			return (0);
		temp++;
	}
	return (i);
}

int	str_valid_numbers(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_valid_number(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_inrange(int numb, int min, int max)
{
	if (numb < min || numb > max)
		return (0);
	return (1);
}