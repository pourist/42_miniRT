/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:16:49 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/26 15:06:30 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "world.h"
#include "parser.h"

/* static void	free_csg(t_shape *csg); */

/* static void	free_group(t_shape *group) */
/* { */
/* 	t_shape	*root; */

/* 	if (!group) */
/* 		return ; */
/* 	root = group->group.root; */
/* 	while (root) */
/* 	{ */
/* 		if (root->is_group) */
/* 			free_group(root); */
/* 		root = root->next; */
/* 	} */
/* 	if (group && group->is_group && group->is_bvh_group) */
/* 	{ */
/* 		free(group); */
/* 		group = NULL; */
/* 	} */
/* 	if (group && group->is_group && group->is_obj_file) */
/* 	{ */
/* 		free_loader_last(group->obj_loader); */
/* 		free(group->obj_loader); */
/* 		group->obj_loader = NULL; */
/* 	} */
/* } */

/* static void	free_csg(t_shape *csg) */
/* { */
/* 	if (csg) */
/* 	{ */
/* 		if (csg->is_csg) */
/* 		{ */
/* 			if (csg->csg.left) */
/* 				free_csg(csg->csg.left); */
/* 			if (csg->csg.right) */
/* 				free_csg(csg->csg.right); */
/* 		} */
/* 		if (csg->is_group) */
/* 			free_group(csg->group); */
/* 		free(csg); */
/* 	} */
/* } */

/* void	free_loader_last(t_obj_loader *loader) */

void	free_world(t_world *world)
{
	int		i;

	i = -1;
	if (world->pattern)
		free_pattern(world->pattern);
	while (++i < world->objs_count)
	{
		if (world->objs[i].is_group && world->objs[i].is_obj_file)
		{
			free_loader_last(world->objs[i].obj_loader);
			free(world->objs[i].obj_loader);
			world->objs[i].obj_loader = NULL;
		}
	}
	if (world->bvh_groups)
	{
		i = -1;
		while (++i < g_bvh_counter)
			free(world->bvh_groups[i]);
		free(world->bvh_groups[i]);
		free(world->bvh_groups);
	}
	free(world->lights);
	free(world->objs);
}

/* void	free_world(t_world *world) */
/* { */
/* 	int		i; */

/* 	i = -1; */
/* 	if (world->pattern) */
/* 		free_pattern(world->pattern); */
/* 	while (++i < world->objs_count) */
/* 	{ */
/* 		if (world->objs[i].is_group) */
/* 			free_group(&world->objs[i]); */
/* 		else if (world->objs[i].is_csg) */
/* 		{ */
/* 			if (world->objs[i].csg.left) */
/* 				free_csg(world->objs[i].csg.left); */
/* 			world->objs[i].csg.left = NULL; */
/* 			if (world->objs[i].csg.right) */
/* 				free_csg(world->objs[i].csg.right); */
/* 			world->objs[i].csg.right = NULL; */
/* 		} */
/* 	} */
/* 	free(world->lights); */
/* 	free(world->objs); */
/* } */
