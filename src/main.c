#include "canvas.h"
#include "lights.h"

/*typedef struct s_minirt
{
	s_light	*A_light;
	int	file;
}	t_minirt;*/

typedef struct s_sub_counts
{
	int	A_light;
	int	camera;
	int	light;
	int	sphere;
	int	plane;
	int	cylinder;
}	t_sub_counts;

int	print_error(char	*text)
{
	write(1, text, ft_strlen(text));
	return (1);
}

int	arg_checker(int argc, char **argv)
{
	char	*format;

	format = ft_strrchr(argv[1], '.');
	if (argc < 2)
		return (print_error("Error: Missing .rt file argument.\n"));
	if (argc > 2)
		return (print_error("Error: Too many arguments.\n"));
	if (format == NULL || ft_strncmp(format, ".rt", 4) != 0)
		return (print_error("Error: Invalid file extension.\n"));
	return (0);
}

void	init_counter(t_sub_counts *count)
{
	count->A_light = 0;
	count->camera = 0;
	count->light = 0;
	count->sphere = 0;
	count->cylinder = 0;
	count->plane = 0;
}

int	start_with(char	*line, char *c)
{

	//////
	//////
	////// TAB AND OTHER EPMTY SPACES ARE NOT HANDLED YET
	////// IF OBJECT IS FOLLOWED BT \n WE DONT COUNT AS IT IS NOT A VALID INPUT	
	//////
	//////

	while (*line && *line == ' ')
		line++;
	if (!ft_strncmp(line, c, ft_strlen(c)))
		return (1);
	return 0;
}

void	subject_counter(t_sub_counts *count, int fd)
{
	char	*temp_line;

	while (1)
	{
		temp_line = get_next_line(fd);
		if (!temp_line || temp_line[0] == '\0')
		{
			free(temp_line);
			break ;
		}
		if (start_with(temp_line, "A "))
			count->A_light++;
		else if (start_with(temp_line, "C "))
			count->camera++;
		else if (start_with(temp_line, "L "))
			count->light++;
		if (start_with(temp_line, "sp "))
			count->sphere++;
		else if (start_with(temp_line, "cy "))
			count->cylinder++;
		else if (start_with(temp_line, "pl "))
			count->plane++;
		free(temp_line);
	}
}

int	parser(int argc, char **argv)
{
	int	fd;
	t_sub_counts	count;

	if (arg_checker(argc, argv))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error("Error: Unable to read the .rt file.\n");
	init_counter(&count);
	subject_counter(&count , fd);
	printf("%d\n", count.A_light);
	return (0);
}

int	main(int argc, char **argv)
{
	//t_minirt	*minirt;

	if (parser(argc, argv))
		return (1);
	return (0);
}
