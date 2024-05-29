#ifndef PARSER_H
# define PARSER_H

# include "lights.h"
# include "world.h"
# include "canvas.h"

#define ERR_INC_AMB "Incorrect ambient lighting elements"
#define OUT_RANGE "out of range"

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

typedef struct s_line_parse_env
{
    char    *temp;
    char    **line;
    int		line_number;
	int		error_type;
	int		type;
}	t_line_parse_env;

typedef enum e_element_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	CYLINDER,
	PLANE,
	EMPTY_LINE,
}	t_element_type;

typedef enum e_error_type
{
	A_RATIO,
	A_OUT_RANGE,
}	t_error_type;

// free_print
int		print_error(char	*text);
int     free_print_error(t_world *minirt, char *str);
int	    free_s(char **s);
// parser_utils
int     is_valid_number(char *str);
int     is_in_range(double numb, double min, double max);
int	    str_valid_numbers(char **str);
int     ft_strarr_len(char **line);
int		are_in_range(char **arr, double min, double max);
// parser
int		parser(int argc, char **argv, t_mini_rt *minirt);
// init_mini_re
int     init_minirt(t_mini_rt *minirt, t_e_counts *count);
// init_ambient
int init_ambient(t_line_parse_env *env, t_world *world);
void    make_ambient(char **rgb, double ratio, t_world *minirt);
// element_counter
int		init_counter_fd(t_e_counts *count, char *file);

#endif
