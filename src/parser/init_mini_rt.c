/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini_rt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:09:00 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/12 10:35:10 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	world->lights = (t_light *)ft_calloc(world->lights_count, sizeof(t_light));
	if (!(world->lights))
		return (print_error(MALLOC_FAIL));
	if (read_lines_init(world, minirt, count))
		return (flush_fd(count->fd), 1);
	return (0);
}

int	init_minirt(t_mini_rt *minirt, t_e_counts *env)
{
	new_world(&minirt->world);
	if (init_mini_rt(&(minirt->world), minirt, env))
		return (free_material(env->material), 1);
	free_material(env->material);
	return (0);
}
