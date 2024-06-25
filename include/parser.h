#ifndef PARSER_H
# define PARSER_H

# include "lights.h"
# include "world.h"
# include "canvas.h"
# include <limits.h>
# include "camera.h"

#define WIDTH 1920
#define HEIGHT 1080

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#define ERR_INC_AMB "Expected format: A <ambient_ratio> <R,G,B>"
#define ERR_INC_CAM "Expected format: C <x,y,z> <orientation x,y,z> <FOV>"
#define ERR_SPHERE "Expected format: sp <x,y,z> <diameter> <R,G,B>"
#define ERR_LIGHT "Expected format: L <x,y,z> <brightness_ratio> <R,G,B>"
#define ERR_PLANE "Expected format: pl <x,y,z> <normal vector> <R,G,B>"
#define ERR_CYLINDER "Expected format: cy <x,y,z> <axis vector> <diameter> <height> <R,G,B>"
#define ERR_CONE "Expected format: cone <base x,y,z> <axis x,y,z> <radius> <height> <is open> <R,G,B>"
#define ERR_CUBE "Expected format: cube <center x,y,z> <width> <height> <depth> <R,G,B>"
#define	RATIO_INVALID "Invalid ambient lighting ratio"
#define RATIO_RANGE "Ambient lighting ratio out of range"
#define RGB_LEN "RGB elements count incorrect."
#define RGB_INVALID "Invalid RGB numbers."
#define RGB_RANGE "RGB values out of range"
#define MALLOC_FAIL "Error\nMemory allocation failed"
#define	ARG_MANY "Error\nToo many arguments"
#define ARG_FEW "Error\nMissing .rt file argument"
#define FILE_FORMAT "Error\nInvalid file extension"
#define FOV_M "Invalid FOV"
#define FOV_RANGE_M "FOV out of range"
#define POV_M "POV elements count incorrect."
#define POV_INVALID_M "Invalid POV numbers."
#define POV_RANGE_M "POV values out of range"
#define OR_M "Orientation Vector elements count incorrect."
#define OR_INVALID_M "Invalid Orientation Vector numbers."
#define OR_RANGE_M "Orientation Vector values out of range"
#define L_RATIO_M "Invalid light brightness ratio"
#define L_RATIO_RANGE_M "Light brightness ratio out of range"
#define POS_M "Light point coordinates count incorrect"
#define POS_INVALID_M "Invalid light point coordinates"
#define POS_RANGE_M "Light point coordinate values out of range"
#define	D_INVALID "Invalid diameter"
#define D_RANGE_M "Diameter out of range"
#define	H_INVALID "Invalid Height"
#define H_RANGE_M "Height out of range"
#define	DEPTH_INVALID "Invalid Depth"
#define DEPTH_RANGE_M "Depth out of range"
#define	W_INVALID "Invalid Width"
#define W_RANGE_M "Width out of range"
#define CENT_M "Center coordinates count incorrect"
#define CENT_INVALID_M "Invalid center coordinates"
#define CENT_RANGE_M "Center coordinate values out of range"
#define NORMAL_M "Normal vector count incorrect"
#define NORMAL_INVALID_M "Invalid Normal vector"
#define NORMAL_RANGE_M "Normal vector values out of range"
#define POINT_COUNT_M "Point coordinates count incorrect."
#define POINT_INVALID_M "Invalid point coordinates."
#define POINT_RANGE_M "Point coordinates values out of range."
#define	R_INVALID "Invalid Radius"
#define R_RANGE_M "Radius out of range"
#define ERR_BOOL "Boolean for 'is open' must be 0 (closed) or 1 (open)"

typedef enum e_error_type
{
	RATIO,
	RATIO_OUT_RANGE,
	RGB,
	RGB_VALID,
	RGB_OUT_RANGE,
	FOV,
	FOV_RANGE,
	POV,
	POV_INVALID,
	POV_RANGE,
	OR,
	OR_INVALID,
	OR_RANGE,
	L_RATIO,
	L_RATIO_RANGE,
	POS,
	POS_INVALID,
	POS_RANGE,
	DIAM,
	DIAM_RANGE,
	CENT,
	CENT_INVALID,
	CENT_RANGE,
	NORMAL,
	NORMAL_INVALID,
	NORMAL_RANGE,
	POINT,
	POINT_INVALID,
	POINT_RANGE,
	HEIGHT_VALID,
	HEIGHT_RANGE,
	RADIUS,
	RADIUS_RANGE,
	OPEN,
	OPEN_RANGE,
	WIDTH_VALID,
	WIDTH_RANGE,
	DEPTH_VALID,
	DEPTH_RANGE,
}	t_error_type;

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
	int	cone;
	int cube;
}	t_e_counts;

typedef struct s_line_parse_env
{
	char	*temp;
	char	**line;
	int		line_number;
	int		error_type;
	int		type;
}	t_line_parse_env;

typedef struct s_cylinder_info
{
	double	diam;
	double	height;
	double	r;
	double	g;
	double	b;

} t_cylinder_info;

typedef enum e_element_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	CYLINDER,
	PLANE,
	CONE,
	CUBE,
	EMPTY_LINE,
}	t_element_type;

// free_print
int		print_error(char	*text);
int     free_print_error(t_world *minirt, char *str);
int	    free_s(char **s);
void	free_mini_rt(t_mini_rt *mini_rt);
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
// error
int		file_error(t_line_parse_env *parse, char *text);
char    *find_error(int type);
// valid args
int 	solo(char *number, double min, double max, t_line_parse_env *env);
int 	triplets(char **triple, double min, double max, t_line_parse_env *env);
// line parser
int 	read_lines_init(t_world *world, t_mini_rt *minirt, int fd);
// camera
int		init_camera(t_line_parse_env *env, t_camera *camera);
// light
int init_light(t_line_parse_env *env, t_light *light);
// sphere
int	init_sphere(t_line_parse_env *env, t_shape *obj);
// plane
int init_plane(t_line_parse_env *env, t_shape *obj);
// cylinder
int init_cylinder(t_line_parse_env *env, t_shape *obj);
// cone
int init_cone(t_line_parse_env *env, t_shape *obj);
// cube 
int init_cube(t_line_parse_env *env, t_shape *obj);

#endif