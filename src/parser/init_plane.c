#include "parser.h"

// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225

void	make_plane(char **rgb, char **normal, char **center, t_shape *obj)
{
	t_vector	vec_default;
	t_vector	vec_user;
	t_matrix	rotation_m; 
	t_matrix	translation_m;
	t_matrix	transform_m;

	new_plane(obj);
	new_color(atof(rgb[0]) * INV_255, atof(rgb[1]) * INV_255,
		atof(rgb[2]) * INV_255, &obj->material.color);
	new_vector(0, 1, 0, &vec_default);
	new_vector(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]),
		&vec_user);
	calculate_rotation_matrix(&vec_default, &vec_user, &rotation_m);
	translation(atof(center[0]), atof(center[1]), atof(center[2]),
		&translation_m);
	multiply_matrices(&translation_m, &rotation_m, &transform_m);
	set_transform(obj, &transform_m);
	free_s(rgb);
	free_s(center);
}

int	init_plane(t_line_parse_env *env, t_shape *obj)
{
	char	**rgb;
	char	**normal;
	char	**point;

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
	return (0);
}
