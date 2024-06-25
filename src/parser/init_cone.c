#include "parser.h"

/*cone 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 true 10,0,255


x,y,z coordinates of the base center of the cone: 50.0,0.0,20.6
3d normalized vector of axis of cone: 0.0,0.0,1.0 
base radius of the cone: 14.2 
height of the cone: 21.42 
is open: true
R,G,B colors: 10, 0, 255  */

typedef struct s_cone_info
{
    double radius;
    double	height;
	double	r;
	double	g;
	double	b;
    bool    open;
} t_cone_info ;

void    make_cone(t_cone_info *cone, char **center, t_shape *obj)
{
    t_matrix    m1;
    t_matrix    m2;
    t_matrix    final;

	new_cone(obj);
	obj->cone.min = 0;
	obj->cone.max = (cone->height * 0.5);
    obj->material.color = new_color(cone->r, cone->g, cone->b);
    translation(ft_atof(center[0]), ft_atof(center[1]), ft_atof(center[2]), &m1);
    scaling(cone->radius * 0.5, 1, cone->radius * 0.5, &m2);
    multiply_matrices(&m1, &m2, &final);
    set_transform(obj, &final);
	free_s(center);
}

int cone_info(t_line_parse_env *env, t_cone_info *cone)
{
    char    **rgb;

    cone->radius = ft_atof(env->line[3]);
    cone->height = ft_atof(env->line[4]);
    env->error_type = RADIUS;
	if (solo(env->line[3], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = HEIGHT_VALID;
	if (solo(env->line[4], EPSILON, (double)INT_MAX, env))
		return (1);
    env->error_type = OPEN;
	if (solo(env->line[5], 0, 1, env))
		return (1);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[6], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
    cone->r = (ft_atof(rgb[0]) / 255);
	cone->g = (ft_atof(rgb[1]) / 255);
	cone->b = (ft_atof(rgb[2]) / 255);
    return (free_s(rgb), 0);
}

int init_cone(t_line_parse_env *env, t_shape *obj)
{
    t_cone_info cone;
    char    **normal;
    char    **center;

    if (ft_strarr_len(env->line) != 7)
		return (file_error(env, ERR_CONE));
    if (cone_info(env, &cone))
        return (1);
    env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
    env->error_type = NORMAL;
	normal = ft_subsplit(env->line[2], ",\n");
	if (triplets(normal, -1, 1, env))
		return (free_s(center), 1);
    make_cone(&cone, center, obj);
    return (0);
}