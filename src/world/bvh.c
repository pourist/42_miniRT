/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:17:45 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/26 17:59:00 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	divide_group(t_shape *group, int threshold, int *bvh_groups_count)
{
	t_shape	*left;
	t_shape	*right;
	t_shape	*current;

	if (!check_group(group, &threshold, bvh_groups_count))
		return ;
	left = NULL;
	right = NULL;
	if (threshold <= group->group.count)
	{
		partition_children(group, &left, &right);
		if (left)
			make_subgroup(group, &left, bvh_groups_count);
		if (right)
			make_subgroup(group, &right, bvh_groups_count);
	}
	current = group->group.root;
	while (current)
	{
		divide_group(current, threshold, bvh_groups_count);
		current = current->next;
	}
	group->bounds_of(group);
}

/* static void	*divide_groups(void *data) */
/* { */
/* 	t_thread_data	*td; */
/* 	t_world			*world; */
/* 	int				index; */

/* 	td = (t_thread_data *)data; */
/* 	if (!td || !td->data) */
/* 		return (ft_putendl_fd("minirt: divide_groups: Wrong arguments", */
/* 				STDERR_FILENO), NULL); */
/* 	world = (t_world *)td->data; */
/* 	if (!world->objs || td->start < 0 || td->end < 0 || td->start >= td->end) */
/* 		return (ft_putendl_fd("minirt: divide_groups: Wrong arguments", */
/* 				STDERR_FILENO), NULL); */
/* 	index = td->start - 1; */
/* 	while (++index < td->end) */
/* 		divide_group(&world->objs[index], BVH_THRESHOLD); */
/* 	return (data); */
/* } */

static void	search_bvh_groups(t_world *world, t_shape *group,
		int *bvh_groups_index, int *bvh_groups_count)
{
	t_shape	*root;

	root = NULL;
	if (!world || !world->objs || !world->objs_count || !group)
		return ;
	if (group->is_bvh_group)
		if (*bvh_groups_index < *bvh_groups_count)
			world->bvh_groups[(*bvh_groups_index)++] = group;
	root = group->group.root;
	while (root)
	{
		if (root->is_group)
			search_bvh_groups(world, root, bvh_groups_index, bvh_groups_count);
		root = root->next;
	}
}

static void	set_bvh_groups(t_world *world, int *bvh_groups_count)
{
	int	i;
	int	bvh_groups_index;

	if (!world || !world->objs || !world->objs_count || !*bvh_groups_count)
		return ;
	world->bvh_groups
		= (t_shape **)ft_calloc(sizeof(t_shape *), *bvh_groups_count + 1);
	if (!world->bvh_groups)
		return ;
	bvh_groups_index = 0;
	i = -1;
	while (++i < world->objs_count)
	{
		if (world->objs[i].is_group)
			search_bvh_groups(world, &world->objs[i], &bvh_groups_index,
				bvh_groups_count);
	}
}

void	create_bvh(t_world *world)
{
	int				i;
	int				bvh_groups_count;

	bvh_groups_count = 0;
	if (!world || !world->objs || !world->objs_count)
		return ;
	i = -1;
	while (++i < world->objs_count)
		divide_group(&world->objs[i], BVH_THRESHOLD, &bvh_groups_count);
	if (bvh_groups_count)
		set_bvh_groups(world, &bvh_groups_count);
}

/* TODO: incorporate threads with correct free at ends */
/* void	create_bvh(t_world *world) */
/* { */
/* 	t_threads_setup	tsetup; */
/* 	t_thread_data	*tdata; */
/* 	pthread_t		*threads; */
/* 	int				i; */

/* 	if (!world || !world->objs || !world->objs_count) */
/* 		return ; */
/* 	if (world->objs_count < 3 */
/* 		|| world->objs_inside_count + world->objs_ext_count < 64) */
/* 	{ */
/* 		i = -1; */
/* 		while (++i < world->objs_count) */
/* 			divide_group(&world->objs[i], BVH_THRESHOLD); */
/* 		return ; */
/* 	} */
/* 	tsetup.nb_iters = world->objs_count; */
/* 	if (!set_threads_data(world, &threads, &tdata, &tsetup)) */
/* 		return ; */
/* 	if (!exec_threads_for(divide_groups, threads, tdata, &tsetup.nb_threads)) */
/* 		return ; */
/* 	printf("BVH groups: %d\n", g_bvh_counter); */
/* 	if (g_bvh_counter) */
/* 		set_bvh_groups(world); */
/* } */
