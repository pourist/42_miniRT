#include "parser.h"

int arg_checker(int argc, char **argv)
{
	char	*format;

	format = ft_strrchr(argv[1], '.');
	if (argc < 2)
		return (print_error("Error: Missing .rt file argument."));
	if (argc > 2)
		return (print_error("Error: Too many arguments."));
	if (format == NULL || ft_strncmp(format, ".rt", 4) != 0)
		return (print_error("Error: Invalid file extension."));
	return (0);
}

void    make_ambient(char **rgb, double ratio, t_world *minirt)
{
    double  r;
    double  g;
    double  b;

    r = (ft_atof(rgb[0]) / 255) * ratio;
    g = (ft_atof(rgb[1]) / 255) * ratio;
    b = (ft_atof(rgb[2]) / 255) * ratio;
    minirt->ambient = new_color(r, g, b);
}

int init_ambient(char **line, t_world *minirt)
{
    double  ratio;
    char    **rgb;

    if (ft_strarr_len(line) != 3)
        return (free_print_error(minirt, "Error\nIncorrect ambient lighting elements."));
    if (!is_valid_number(line[1]))
        return (free_print_error(minirt, "Error\nInvalid ambient lighting ratio."));
    ratio = ft_atof(line[1]);
    if (ratio < 0 || ratio > 1)
        return(free_print_error(minirt, "Error\nAmbient lighting ratio out of range."));
    rgb = ft_split(line[2], ',');
    if (ft_strarr_len(rgb) != 3 || !str_valid_numbers(rgb) || !rgb[2][0])
    {
        free_s(rgb);
        return (free_print_error(minirt, "Error\nRGB elements count incorrect or invalid numbers."));
    }
    if (!is_inrange(ft_atoi(rgb[0]), 0 , 255) || !is_inrange(ft_atoi(rgb[1]), 0 , 255) || !is_inrange(ft_atoi(rgb[2]), 0 , 255))
    {
        free_s(rgb);
        return (free_print_error(minirt, "Error\nRGB values out of range."));
    }
    make_ambient(rgb, ft_atof(line[1]),minirt);
    free_s(rgb);
    return (0);
}

int read_lines_init(t_world *minirt)
{
    char    *temp_line;
    char    **line;

    while (1)
    {
        temp_line = get_next_line(minirt->fd);
		if (!temp_line || temp_line[0] == '\0')
		{
			free(temp_line);
			break ;
		}
		line = ft_split (temp_line, ' ');
		free(temp_line);
        if (!ft_strncmp(line[0], "A", 2) && init_ambient(line, minirt))
            return (free_s(line));
        free_s(line);
    }
    return (0);
}

int     init_minirt(t_world *minirt, t_e_counts *count)
{
    int objs_count;

    objs_count = count->cylinder + count->sphere + count->plane; /////////right? :D
    minirt->objs_count = objs_count;
    minirt->lights_count = count->light;
    minirt->xs = NULL;
    minirt->objs = (t_shape *)malloc(sizeof(t_shape) * (objs_count));
    if (!minirt->objs)
        return (print_error("Error\nMemory allocation failed."));
    minirt->lights = (t_light *)malloc(sizeof(t_light) * (minirt->lights_count));
    if (!minirt->lights)
    {
        free(minirt->objs);
        return (print_error("Error\nMemory allocation failed."));
    }
    if (read_lines_init(minirt))
        return (1);
    return (0);
}

int	parser(int argc, char **argv, t_world *minirt)
{
	int			fd;
	t_e_counts	count;

	if (arg_checker(argc, argv))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error("Error: Unable to read the .rt file.");
	if (elements_count_checker(&count, fd))
        return (1);
    minirt->fd = open(argv[1], O_RDONLY);
    if (init_minirt(minirt, &count))
        return (1);
    else
	    return (0);
}
