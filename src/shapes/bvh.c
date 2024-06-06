#include "groups.h"

void	split_bounds(t_bounds s_box[2])
{
	double	dxyz[3];
	double	greatest;

	dxyz[0] = s_box[0].max.x - s_box[0].min.x;
	dxyz[1] = s_box[0].max.y - s_box[0].min.y;
	dxyz[2] = s_box[0].max.z - s_box[0].min.z;
	greatest = ft_max(dxyz[0], dxyz[1], dxyz[2]);
	if (greatest == dxyz[0])
	{
		s_box[0].max.x = s_box[0].min.x + dxyz[0] * 0.5;
		s_box[1].min.x = s_box[0].max.x;
	}
	else if (greatest == dxyz[1])
	{
		s_box[0].max.y = s_box[0].min.y + dxyz[1] * 0.5;
		s_box[1].min.y = s_box[0].max.y;
	}
	else
	{
		s_box[0].max.z = s_box[0].min.z + dxyz[2] * 0.5;
		s_box[1].min.z = s_box[0].max.z;
	}
}

void	fill_containers(t_shape *group, t_shape **left, t_shape **right,
			t_bounds split_box[2])
{
	t_shape	**current;
	t_shape	*tmp;

	current = &group->group.root;
	while (*current)
	{
		tmp = *current;
		if (box_contains_box(&split_box[0], &tmp->bounds))
		{
			*current = tmp->next;
			tmp->next = *left; 
			*left = tmp;
			group->group.count--;
		}
		else if (box_contains_box(&split_box[1], &tmp->bounds))
		{
			*current = tmp->next;
			tmp->next = NULL;
			tmp->next = *right; 
			*right = tmp;
			group->group.count--;
		}
		else
			current = &tmp->next;
	}
}

void	partition_children(t_shape *group, t_shape **left, t_shape **right)
{
	t_bounds	split_box[2];

	if (!group)
		return ;
	if (!group->is_bounds_precal)
		group->bounds_of(group);
	split_box[0] = group->bounds;
	split_box[1] = group->bounds;
	split_bounds(split_box);
	fill_containers(group, left, right, split_box);
	group->bounds_of(group);
}

void	make_subgroup(t_shape *group, t_shape **container)
{
	t_shape	*subgroup;
	t_shape	*tmp;
	t_shape	*current;

	if (!group || !container || !(*container))
		return ;
	subgroup = (t_shape *)malloc(sizeof(t_shape));
	if (!subgroup)
		return ;
	new_group(subgroup);
	current = *container;
	while (current)
	{
		tmp = current;
		current = current->next;
		tmp->next = NULL;
		add_child(subgroup, tmp);
	}
	add_child(group, subgroup);
}

bool	check_group(t_shape *group, int threshold)
{
	if (!group || (group && (!group->is_group && !group->is_csg)))
		return (false);
	if (!group->is_bounds_precal)
		group->bounds_of(group);
	if (group->is_csg)
	{
		divide_groups(group->csg.left, threshold);
		divide_groups(group->csg.right, threshold);
		return (false);
	}
	return (true);
}

void	divide_groups(t_shape *group, int threshold)
{
	t_shape	*left;
	t_shape	*right;
	t_shape	*current;

	if (!check_group(group, threshold))
		return ;
	left = NULL;
	right = NULL;
	if (threshold <= group->group.count)
	{
		partition_children(group, &left, &right);
		if (left)
			make_subgroup(group, &left);
		if (right)
			make_subgroup(group, &right);
	}
	current = group->group.root;
	while (current)
	{
		divide_groups(current, threshold);
		current = current->next;
	}
	group->bounds_of(group);
}

// void	create_bvh(t_world *world)

// {
// 	int	i;

// 	if (!world)
// 		return ;
// 	new_group(&world->bvh);
// 	i = -1;
// 	while (++i < world->objs_count)
// 		add_child(&world->bvh[0], &world->objs[i]);
// 	// world->bvh[0].bounds_of(&world->bvh[0]);
// 	// divide_tree(&world->bvh[0], &world->bvh[1], &world->bvh[2]);
// 	world->bvh[0].is_bounds_precal = false;
// 	// world->bvh[1].is_bounds_precal = false;
// 	// world->bvh[2].is_bounds_precal = false;
// 	world->bvh[0].bounds_of(&world->bvh[0]);
// 	// world->bvh[1].bounds_of(&world->bvh[1]);
// 	// world->bvh[2].bounds_of(&world->bvh[2]);
// }
