/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:29:39 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/26 11:20:46 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	make_obj(char *name, t_e_obj *o, t_shape *obj, t_world *world)
{
	t_vector		axis_v;
	t_vector		default_axis;
	t_matrix		m[4];

	new_vector(0, 1, 0, &default_axis);
	new_vector(ft_atof(o->axis[0]), ft_atof(o->axis[1]),
		ft_atof(o->axis[2]), &axis_v);
	scaling(ft_atof(o->scale[0]), ft_atof(o->scale[1]),
		ft_atof(o->scale[2]), &m[2]);
	calculate_rotation_matrix(&default_axis, &axis_v, &m[1]);
	translation(ft_atof(o->center[0]), ft_atof(o->center[1]),
		ft_atof(o->center[2]), &m[0]);
	multiply_matrices(&m[0], multiply_matrices(&m[2], &m[1], &m[3]), &m[3]);
	obj->obj_loader = (t_obj_loader *)malloc(sizeof(t_obj_loader));
	new_obj_loader(obj->obj_loader, obj);
	parse_obj_file(obj->obj_loader, name);
	world->objs_ext_count
		+= obj->obj_loader->t_count + obj->obj_loader->gp_count;
	set_transform(obj, &m[3]);
	free_s(o->center);
	free_s(o->axis);
	free_s(o->scale);
}

int	init_obj(t_line_parse_env *env, t_shape *obj, t_world *world)
{
	t_e_obj	e_obj;
	bool	material;

	material = false;
	if (ft_strarr_len(env->line) == 6)
		material = 1;
	else if (ft_strarr_len(env->line) != 5)
		return (file_error(env, ERR_OBJ));
	env->error_type = CENT;
	e_obj.center = ft_subsplit(env->line[2], ",\n");
	if (triplets(e_obj.center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = NORMAL_;
	e_obj.axis = ft_subsplit(env->line[3], ",\n");
	if (triplets(e_obj.axis, (double)INT_MIN, (double)INT_MAX, env))
		return (free_s(e_obj.center), 1);
	env->error_type = SCALE;
	e_obj.scale = ft_subsplit(env->line[4], ",\n");
	if (triplets(e_obj.scale, -1, (double)INT_MAX, env))
		return (free_s(e_obj.axis), free_s(e_obj.center), 1);
	make_obj(env->line[1], &e_obj, obj, world);
	if (material && find_material(env->material, obj, env->line[5], env))
		return (1);
	return (0);
}
