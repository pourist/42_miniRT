/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini_rt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:09:00 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/27 22:54:05 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_predef_camera(t_mini_rt *minirt)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(&minirt->camera, WIDTH, HEIGHT, M_PI_2);
	new_point(0, 0, 0.1, &from);
	new_point(0, 0, -0.1, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(&minirt->camera, view_transform(&from, &to, &up,
			&minirt->camera.transform));
}

int	init_mini_rt(t_world *world, t_mini_rt *minirt, t_e_counts *count)
{
	int	objs_count;

	objs_count = count->cylinder + count->sphere + count->plane
		+ count->cone + count->cube + count->ob;
	world->objs_count = objs_count;
	world->lights_count = count->light + count->other_light;
	world->objs = (t_shape *)ft_calloc(objs_count, sizeof(t_shape));
	if (!world->objs)
		return (print_error(MALLOC_FAIL));
	if (world->lights_count)
	{
		world->lights = (t_light *)ft_calloc(world->lights_count,
				sizeof(t_light));
		if (!(world->lights))
			return (print_error(MALLOC_FAIL));
	}
	if (count->camera == 0)
		init_predef_camera(minirt);
	if (read_lines_init(world, minirt, count))
		return (flush_fd(count->fd), 1);
	return (0);
}

int	init_minirt(t_mini_rt *minirt, t_e_counts *env)
{
	new_world(&minirt->world);
	if (init_mini_rt(&(minirt->world), minirt, env))
		return (free_pat_mat(env), 1);
	free_material(env->material);
	minirt->world.pattern = env->pat;
	return (0);
}
