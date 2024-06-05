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

void	insert_shape(t_shape **root, t_shape *shape)
{
	t_shape	*current;

	if (!root || !(*root))
	{
		if (root)
			(*root) = shape;
		return ;
	}
	shape->next = NULL;
	current = *root;
	while (current->next)
		current = current->next;
	current->next = shape;
}

bool	set_split_box(t_shape *group, t_bounds split_box[2])
{
	if (!group) 
		return (false);
	if (!group->is_bounds_precal)
		group->bounds_of(group);
	split_box[0] = group->bounds;
	split_box[1] = group->bounds;
	split_bounds(split_box);
	return (true);
}

void	partition_children(t_shape *group, t_shape **left, t_shape **right)
{
	t_shape		**current;
	t_shape		*tmp;
	t_bounds	split_box[2];

	if (!set_split_box(group, split_box))
		return ;
	current = &group->group.root;
	while (*current)
	{
		tmp = *current;
		if (!tmp->is_bounds_precal)
			tmp->bounds_of(tmp);
		if (box_contains_box(&split_box[0], &tmp->bounds))
		{
			*current = tmp->next;
			insert_shape(left, tmp);
		}
		else if (box_contains_box(&split_box[1], &tmp->bounds))
		{
			*current = tmp->next;
			insert_shape(right, tmp);
		}
		else
			current = &tmp->next;
	}
}

// void	divide_tree(t_shape *root, t_shape *left, t_shape *right)
// {
// 	if (!root)
// 		return ;
// 	if (root->left)
// 		divide_tree(root->left, left, right);
// 	if (root->right)
// 		divide_tree(root->right, left, right);
// 	if (!root->left && !root->right)
// 		return ;
// 	partition_children_group(root, left, right);
// }

// void	create_bvh(t_world *world)

// {
// 	int	i;

// 	if (!world)
// 		return ;
// 	new_group(&world->bvh[0]);
// 	new_group(&world->bvh[1]);
// 	new_group(&world->bvh[2]);
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
