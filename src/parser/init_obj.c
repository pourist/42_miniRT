/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:29:39 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/29 08:27:20 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_rotations(t_e_obj *obj, t_matrix *transform_m)
{
	t_matrix	m;

	if (obj->trx != 0)
		rotation_x(cos(obj->trx), sin(obj->trx), &m);
	if (obj->try != 0)
		rotation_y(cos(obj->try), sin(obj->try), &m);
	if (obj->trz != 0)
		rotation_z(cos(obj->trz), sin(obj->trz), &m);
	if (obj->trx != 0 || obj->try != 0 || obj->trz != 0)
		multiply_matrices(&m, transform_m, transform_m);
}

void	make_obj(char *name, t_e_obj *o, t_shape *obj, t_world *world)
{
	t_vector		default_axis;
	t_matrix		m[4];

	obj->cast_shadow = o->cast_shadow;
	new_vector(0, 1, 0, &default_axis);
	calculate_rotation_matrix(&default_axis, &o->axis, &m[1]);
	get_identity_matrix(&m[3]);
	set_rotations(o, &m[3]);
	multiply_matrices(&m[3], &m[1], &m[1]);
	scaling(o->scale.x, o->scale.y, o->scale.z, &m[2]);
	translation(o->center.x, o->center.y, o->center.z, &m[0]);
	multiply_matrices(&m[0], multiply_matrices(&m[2], &m[1], &m[3]), &m[3]);
	obj->obj_loader = (t_obj_loader *)malloc(sizeof(t_obj_loader));
	new_obj_loader(obj->obj_loader, obj);
	parse_obj_file(obj->obj_loader, name);
	world->objs_ext_count
		+= obj->obj_loader->t_count + obj->obj_loader->gp_count;
	set_transform(obj, &m[3]);
}

static bool	obj_info_2(t_line_parse_env *env, t_e_obj *obj)
{
	char	**center;
	char	**axis;
	char	**scale;

	env->error_type = CENT;
	center = ft_subsplit(env->line[2], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (false);
	new_point(ft_atof(center[0]), ft_atof(center[1]),
		ft_atof(center[2]), &obj->center);
	env->error_type = NORMAL_;
	axis = ft_subsplit(env->line[3], ",\n");
	if (triplets(axis, (double)INT_MIN, (double)INT_MAX, env))
		return (free_s(center), false);
	new_vector(ft_atof(axis[0]), ft_atof(axis[1]),
		ft_atof(axis[2]), &obj->axis);
	env->error_type = SCALE;
	scale = ft_subsplit(env->line[4], ",\n");
	if (triplets(scale, -1, (double)INT_MAX, env))
		return (free_s(axis), free_s(center), false);
	new_point(ft_atof(scale[0]), ft_atof(scale[1]),
		ft_atof(scale[2]), &obj->scale);
	return (free_s(axis), free_s(center), free_s(scale), true);
}

static bool	obj_info_1(t_line_parse_env *env, t_e_obj *obj, int *len)
{
	int	i;

	obj->trx = 0;
	obj->try = 0;
	obj->trz = 0;
	obj->material = false;
	if (*len >= 7)
	{
		i = 5;
		while (env->line[++i])
		{
			if (ft_strncmp(env->line[i], "Trx", 4) == 0)
				obj->trx = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Try", 4) == 0)
				obj->try = ft_atof(env->line[++i]);
			else if (ft_strncmp(env->line[i], "Trz", 4) == 0)
				obj->trz = ft_atof(env->line[++i]);
			else if ((i == 6 && i == *len - 1) || (i == *len - 1
					&& (obj->trx != 0 || obj->try != 0 || obj->trz != 0)))
				obj->material = true;
			else
				return (false);
		}
	}
	return (true);
}

int	init_obj(t_line_parse_env *env, t_shape *obj, t_world *world)
{
	t_e_obj	e_obj;
	int		len;

	len = ft_strarr_len(env->line);
	if (!obj_info_1(env, &e_obj, &len) || len < 6)
		return (file_error(env, ERR_OBJ));
	if (!obj_info_2(env, &e_obj))
		return (1);
	env->error_type = SHADOWS;
	if (solo(env->line[5], 0, 1, env))
		return (1);
	e_obj.cast_shadow = ft_atoi(env->line[5]);
	make_obj(env->line[1], &e_obj, obj, world);
	if (e_obj.material && find_material(env->material, obj,
			env->line[len - 1], env))
		return (1);
	return (0);
}
