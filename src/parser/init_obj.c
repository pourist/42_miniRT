#include "parser.h"

void	make_obj(char *name, t_e_obj *o, t_shape *obj, t_world *world)
{
	t_vector axis_v;
	t_vector default_axis;
	t_matrix m[4];
	t_obj_loader loader;
  
	new_vector(0, 1, 0, &default_axis);
	new_vector(ft_atof(o->axis[0]), ft_atof(o->axis[1]), 
			ft_atof(o->axis[2]), &axis_v);
	scaling(ft_atof(o->scale[0]), ft_atof(o->scale[1]), 
			ft_atof(o->scale[2]), &m[2]);
	calculate_rotation_matrix(&default_axis, &axis_v, &m[1]);
	translation(ft_atof(o->center[0]), ft_atof(o->center[1]), 
			ft_atof(o->center[2]), &m[0]);
	multiply_matrices(&m[0], multiply_matrices(&m[2], &m[1], &m[3]), &m[3]);
	set_transform(obj, &m[3]);
	new_obj_loader(&loader, obj);
	parse_obj_file(&loader, name);
	world->objs_ext_count += loader.t_count + loader.gp_count;
}

int	init_obj(t_line_parse_env *env, t_shape *obj, t_world *world)
{
	t_e_obj	e_obj;

	if (ft_strarr_len(env->line) != 5)
		return (file_error(env, ERR_OBJ));
	env->error_type = CENT;
	e_obj.center = ft_subsplit(env->line[2], ",\n");
	if (triplets(e_obj.center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = NORMAL_;
	e_obj.axis = ft_subsplit(env->line[3], ",\n");
	if (triplets(e_obj.axis, -1, 1, env))
		return (free_s(e_obj.center), 1);
	env->error_type = SCALE;
	e_obj.scale = ft_subsplit(env->line[4], ",\n");
	if (triplets(e_obj.axis, 0, (double)INT_MAX, env))
		return (free_s(e_obj.axis), free_s(e_obj.center), 1);
	make_obj(env->line[1], &e_obj, obj, world);
	free_s(e_obj.center);
	free_s(e_obj.axis);
	free_s(e_obj.scale);
	return(0);
}
