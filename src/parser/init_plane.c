#include "parser.h"

// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225


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
	if (triplets(point, -1, 1, env))
	{
		free_s(normal);
		return (free_s(rgb), 1);
	}
	(void)obj;
	return(0);
}