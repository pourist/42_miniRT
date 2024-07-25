/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:16:49 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:16:51 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "world.h"
#include "parser.h"

static void	free_csg(t_shape *csg);

static void	free_group(t_shape *root)
{
	t_shape	*tmp;

	while (root)
	{
		if (root->is_group)
			free_group(root->group.root);
		tmp = root;
		root = root->next;
		free(tmp);
	}
	root = NULL;
}

static void	free_csg(t_shape *csg)
{
	if (csg)
	{
		if (csg->is_csg)
		{
			if (csg->csg.left)
				free_csg(csg->csg.left);
			csg->csg.left = NULL;
			if (csg->csg.right)
				free_csg(csg->csg.right);
			csg->csg.right = NULL;
		}
		if (csg->is_group)
		{
			free_group(csg->group.root);
			csg->group.root = NULL;
		}
		free(csg);
	}
}

void	free_world(t_world *world)
{
	int		i;

	i = -1;
	if (world->pattern)
		free_pattern(world->pattern);
	while (++i < world->objs_count)
	{
		if (world->objs[i].is_group)
		{
			free_group(world->objs[i].group.root);
			world->objs[i].group.root = NULL;
		}
		if (world->objs[i].is_csg)
		{
			if (world->objs[i].csg.left)
				free_csg(world->objs[i].csg.left);
			world->objs[i].csg.left = NULL;
			if (world->objs[i].csg.right)
				free_csg(world->objs[i].csg.right);
			world->objs[i].csg.right = NULL;
		}
	}
	free(world->lights);
	free(world->objs);
}
