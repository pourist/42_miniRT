#include "parser.h"

void make_obj(char *name, char **center, char **axis, t_shape *obj)
{
    t_vector axis_v;
    t_vector default_axis;
    t_matrix trans_m;
    t_matrix rot_m;
    t_matrix final_m;
    t_obj_loader loader;

    new_vector(0, 1, 0, &default_axis);
    new_vector(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]), &axis_v);
    calculate_rotation_matrix(&default_axis, &axis_v, &rot_m);
    translation(ft_atof(center[0]), ft_atof(center[1]), ft_atof(center[2]), &trans_m);
    multiply_matrices(&rot_m, &trans_m, &final_m);
    set_transform(obj, &final_m);
    new_obj_loader(&loader, obj);
    parse_obj_file(&loader, name);
}

int init_obj(t_line_parse_env *env, t_shape *obj)
{
    char    **center;
    char    **axis;

    if (ft_strarr_len(env->line) != 4)
		return (file_error(env, ERR_OBJ));
	env->error_type = CENT;
	center = ft_subsplit(env->line[2], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = NORMAL_;
	axis = ft_subsplit(env->line[3], ",\n");
	if (triplets(axis, -1, 1, env))
		return (free_s(center), 1);
    make_obj(env->line[1], center, axis, obj);
    free_s(center);
    free_s(axis);
    return(0);
}