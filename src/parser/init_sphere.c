#include "parser.h"


// Sphere:
// sp 0.0,0.0,20.6 12.6 10,0,255
// ∗ identifier: sp
// ∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// ∗ the sphere diameter: 12.6
// ∗ R,G,B colors in range [0-255]: 10, 0, 255

void    make_sphere(char **rgb, double diam, char **center, t_shape *obj)
{
    t_matrix    m1;
    t_matrix    m2;
    t_matrix    final;
	double	r;
	double	g;
	double	b;

	r = (ft_atof(rgb[0]) / 255);
	g = (ft_atof(rgb[1]) / 255);
	b = (ft_atof(rgb[2]) / 255);
	new_sphere(obj);
    obj->material.color = new_color(r, g, b);
    m1 = translation(ft_atof(center[0]), ft_atof(center[1]), ft_atof(center[2]));
    m2 = scaling(diam * 0.5, diam * 0.5, diam * 0.5);
    //m2 = scaling(20,20,20);
    final = multiply_matrices(m1, m2);
    set_transform(obj, final);
    //set_transform(obj, scaling(0.5, 0.5, 0.5));
    (void)diam;
}

int	init_sphere(t_line_parse_env *env, t_shape *obj)
{
	char	**center;
    char	**rgb;

	if (ft_strarr_len(env->line) != 4)
		return (file_error(env, ERR_SPHERE));
	env->error_type = D_SPHERE;
	if (solo(env->line[2], EPSILON, (double)INT_MAX, env))
		return (1);
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[3], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (free_s(center), 1);
    make_sphere(rgb, ft_atof(env->line[2]), center, obj);
    return (0);
}