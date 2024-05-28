#ifndef PARSER_H
# define PARSER_H

# include "canvas.h"
# include "lights.h"
# include "world.h"

typedef struct s_e_counts
{
	int	a_light;
	int	camera;
	int	light;
	int	sphere;
	int	plane;
	int	cylinder;
	int	unknown;
}	t_e_counts;

// utils
int		start_with(char	*line, char *c);
void    elements_counter(t_e_counts *count, int fd, char *line);
int     elements_count_checker(t_e_counts *count, int fd);
int		arg_checker(int argc, char **argv);
int		print_error(char	*text);
int     is_valid_number(char *str);
int     free_print_error(t_world *minirt, char *str);
int	    free_s(char **s);
int     is_inrange(int numb, int min, int max);
int	    str_valid_numbers(char **str);
int     ft_strarr_len(char **line);
// parser
int		parser(int argc, char **argv, t_world *minirt);

#endif
