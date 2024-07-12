/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:39:43 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/12 09:42:00 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

double	degrees_to_radian(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	make_camera(t_camera *camera, double fov, char **pov, char **or)
{
	t_point		from;
	t_vector	direction;
	t_vector	up;

	new_vector(ft_atof(or[0]), ft_atof(or[1]), ft_atof(or[2]), &direction);
	new_camera(camera, WIDTH, HEIGHT, degrees_to_radian(fov));
	new_point(ft_atof(pov[0]), ft_atof(pov[1]), ft_atof(pov[2]), &from);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform_with_direction(&from,
			&direction, &up, &camera->transform));
}

static bool	set_dof(t_camera *camera, t_line_parse_env *env)
{
	env->error_type = DOF;
	if (env->line[5] && solo((env->line[5]), 0, INT_MAX, env))
		return (false);
	camera->aperture_size = ft_atof(env->line[5]);
	if (env->line[6] && solo((env->line[6]), 0, INT_MAX, env))
		return (false);
	camera->focal_length = ft_atof(env->line[6]);
	if (env->line[7] && solo((env->line[7]), 0, INT_MAX, env))
		return (false);
	camera->color_variance_limit = ft_atof(env->line[7]);
	if (env->line[8] && solo((env->line[8]), 0, 1, env))
		return (false);
	camera->supersampling = ft_atoi(env->line[8]);
	if (env->line[9] && solo((env->line[9]), 0, INT_MAX, env))
		return (false);
	camera->samples = ft_atoi(env->line[9]);
	return (true);
}

int	init_camera(t_line_parse_env *env, t_camera *camera)
{
	char	**pov;
	char	**orientation;

	if (ft_strarr_len(env->line) < 4 || ft_strncmp(env->line[4], "DOF", 3))
		return (file_error(env, ERR_INC_CAM));
	env->error_type = FOV;
	if (solo((env->line[3]), 0, 180, env))
		return (1);
	env->error_type = POV;
	pov = ft_subsplit(env->line[1], ",\n");
	if (triplets(pov, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = OR;
	orientation = ft_subsplit(env->line[2], ",\n");
	if (triplets(orientation, -1, 1, env))
		return (free_s(pov), 1);
	make_camera(camera, ft_atof(env->line[3]), pov, orientation);
	if (env->line[4] && ft_strncmp(env->line[4], "DOF", 4) == 0 && env->line[5])
		if (!set_dof(camera, env))
			return (free_s(pov), free_s(orientation), 1);
	free_s(pov);
	free_s(orientation);
	return (0);
}
