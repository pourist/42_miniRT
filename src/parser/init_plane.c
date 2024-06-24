#include "parser.h"

// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225


t_matrix    *align_plane_normal(t_vector *default_normal, t_vector *user_normal,
        t_matrix *rotation_matrix)
{
    double        cos_theta;
    double        theta;
    t_vector    rotation_axis;
   // double        magnitude_axis;

    cos_theta = dot(default_normal, user_normal);
    theta = acos(cos_theta);
    cross(default_normal, user_normal, &rotation_axis);
	normalize(&rotation_axis, &rotation_axis);
    // magnitude_axis = sqrt(magnitude_squared(&rotation_axis));
    // rotation_axis.x /= magnitude_axis;
    // rotation_axis.y /= magnitude_axis;
    // rotation_axis.z /= magnitude_axis;
	printf("---theta : %f-- x : %f y = %f z = %f---\n", theta, rotation_axis.x, rotation_axis.y, rotation_axis.z);
    if (rotation_axis.x == 1)
        rotation_x(cos(theta), sin(theta), rotation_matrix);
    else if (rotation_axis.y == 1)
        rotation_y(cos(theta), sin(theta), rotation_matrix);
    else if (rotation_axis.z == 1)
        rotation_z(cos(theta), sin(theta), rotation_matrix);
    return (rotation_matrix);
}

void    make_plane(char **rgb, char **normal, char **center, t_shape *obj)
{
    t_matrix    m1;
    t_matrix    m2;
    t_matrix    final;
	double	r;
	double	g;
	double	b;
	t_vector norm[2];

	r = (ft_atof(rgb[0]) / 255);
	g = (ft_atof(rgb[1]) / 255);
	b = (ft_atof(rgb[2]) / 255);
	new_plane(obj);
    obj->material.color = new_color(r, g, b);
    translation(ft_atof(center[0]), ft_atof(center[1]), ft_atof(center[2]), &m1);
	new_vector(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]), &norm[0]);
	align_plane_normal(new_vector(0, 1, 0 , &norm[1]), &norm[0], &m2);
    multiply_matrices(&m2, &m1, &final);
    set_transform(obj, &m1);
	free_s(rgb);
	free_s(center);
}


int init_plane(t_line_parse_env *env, t_shape *obj)
{
    char    **rgb;
    char    **normal;
    char    **point;

    if (ft_strarr_len(env->line) != 4)
		return (file_error(env, ERR_PLANE));
	env->error_type = RGB;
    rgb = ft_subsplit(env->line[3], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	env->error_type = NORMAL;
	normal = ft_subsplit(env->line[2], ",\n");
	if (triplets(normal, -1, 1, env))
		return (free_s(rgb), 1);
	point = ft_subsplit(env->line[1], ",\n");
	env->error_type = POINT;
	if (triplets(point, (double)INT_MIN, (double)INT_MAX, env))
	{
		free_s(normal);
		return (free_s(rgb), 1);
	}
	make_plane(rgb, normal, point, obj);
	return(0);
}