#ifndef PARSER_H
# define PARSER_H

# include "lights.h"
# include "world.h"
# include "canvas.h"

typedef struct s_e_counts
{
	int	a_light;
	int	camera;
	int	light;
	int	sphere;
	int	plane;
	int	cylinder;
	int	unknown;
	int	fd;
}	t_e_counts;

// free_print
int		print_error(char	*text);
int     free_print_error(t_world *minirt, char *str);
int	    free_s(char **s);
// parser_utils
int     is_valid_number(char *str);
int     is_inrange(int numb, int min, int max);
int	    str_valid_numbers(char **str);
int     ft_strarr_len(char **line);
// parser
int		parser(int argc, char **argv, t_mini_rt *minirt);
// init_mini_re
int     init_minirt(t_mini_rt *minirt, t_e_counts *count);
// init_ambient
int		init_ambient(char **line, t_world *minirt);
void    make_ambient(char **rgb, double ratio, t_world *minirt);
// element_counter
int		init_counter_fd(t_e_counts *count, char *file);

#endif
