#include "parser.h"

int	arg_checker(int argc, char **argv)
{
	char	*format;

	format = ft_strrchr(argv[1], '.');
	if (argc < 2)
		return (print_error(ARG_FEW));
	if (argc > 2)
		return (print_error(ARG_MANY));
	if (format == NULL || ft_strncmp(format, ".rt", 4) != 0)
		return (print_error(FILE_FORMAT));
	return (0);
}

int	init_material(char **line, int line_num, t_material *material)
{
	(void)(material);
	(void)line;
	(void)line_num;
	return(0);
}

int	read_material(t_e_counts *count, char *file)
{
	char	*temp_line;
	char	**line;
	int		index;
	int		line_num;

	line_num = 0;
	index = 0;
	count->material = (t_material**)malloc(sizeof(t_material*) * count->mat);
	while (1)
	{
		temp_line = get_next_line(count->fd);
		if (!temp_line || temp_line[0] == '\0')
		{
			free(temp_line);
			break;
		}
		line = ft_split (temp_line, ' ');
		free(temp_line);
		if (!ft_strncmp(line[0], "material", 10))
		{
			if (init_material(line, line_num, count->material[index]))
				return(free_s(line), 1);
			index++;
		}
		line_num++;
		free_s(line);
	}
	close(count->fd);
	count->fd = open(file, O_RDONLY);
	return(0);
}

int	parser(int argc, char **argv, t_mini_rt *minirt)
{
	t_e_counts	count;

	if (arg_checker(argc, argv))
		return (1);
	if (init_counter_fd(&count, argv[1]))
		return (1);
	if (read_material(&count, argv[1]))
		return (1);
	if (init_minirt(minirt, &count))
		return (free_mini_rt(minirt), 1);
	return (0);
}
	