#include "parser.h"

/*
cube 0.0,0.0,0.0 5.0 5.0 5.0 10,0,255

x,y,z coordinates of the center of the cube: 0.0,0.0,0.0 (Center position of the cube.)
width of the cube: 5.0 (Width of the cube along the x-axis.)
height of the cube: 5.0 (Height of the cube along the y-axis.)
depth of the cube: 5.0 (Depth of the cube along the z-axis.)
R,G,B colors: 10, 0, 255 (Colors of the cube in RGB format, where each component is in the range [0-255].)
*/

typedef struct s_cube_info
{
    double  width;
    double  height;
    double  depth;
}   t_cube_info;

// void    make_cube(t_cube_info *cube, char **center, char **rgb, t_shape *obj)
// {
//     new_cube(obj);
    
// }

int cube_info(t_line_parse_env *env, t_cube_info *cube)
{
    cube->depth = ft_atof(env->line[4]);
    cube->height = ft_atof(env->line[3]);
    cube->width = ft_atof(env->line[2]);
    env->error_type = HEIGHT_VALID;
	if (solo(env->line[3], EPSILON, (double)INT_MAX, env))
		return (1);
    env->error_type = WIDTH_VALID;
	if (solo(env->line[2], EPSILON, (double)INT_MAX, env))
		return (1);
    env->error_type = DEPTH_VALID;
	if (solo(env->line[4], EPSILON, (double)INT_MAX, env))
		return (1);
    return (0);
}

int init_cube(t_line_parse_env *env, t_shape *obj)
{
    t_cube_info cube;
    char    **rgb;
    char    **center;

    if (ft_strarr_len(env->line) != 6)
		return (file_error(env, ERR_CUBE));
    if (cube_info(env, &cube))
    {
        return (1);
    }
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
    env->error_type = RGB;
    rgb = ft_subsplit(env->line[5], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (free_s(center), 1);
//    (void)obj;
    (void)obj;
    free_s(rgb);
    free_s(center);
    return (1);
}