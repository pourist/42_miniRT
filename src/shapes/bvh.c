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

void	insert_to(t_shape *left, t_shape *right, t_shape **root, t_bounds s_box[2])
{
	if (!root || !(*root))
		return ;
	if (box_contains_box(&s_box[0], &(*root)->bounds))
	{
		printf("left\n");
		left->is_bounds_precal = false;
		(*root)->is_bounds_precal = false;
		if (!left->left)
			left->left = *root;
		else if (!left->right)
			left->right = *root;
		else
			btree_insert(&left, *root);
	}
	else if (box_contains_box(&s_box[1], &(*root)->bounds))
	{
		printf("right\n");
		right->is_bounds_precal = false;
		(*root)->is_bounds_precal = false;
		if (!right->left)
			right->left = *root;
		else if (!right->right)
			right->right = *root;
		else
			btree_insert(&right, *root);
	}
}

void	partition_children_group(t_shape *root, t_shape *left, t_shape *right)
{
	if (!root)
		return ;
	root->bounds_of(root);
	insert_to(left, right, &root, root->split_box);
}

void	divide_tree(t_shape *root, t_shape *left, t_shape *right)
{
	if (!root)
		return ;
	if (root->left)
		divide_tree(root->left, left, right);
	if (root->right)
		divide_tree(root->right, left, right);
	if (!root->left && !root->right)
		return ;
	partition_children_group(root, left, right);
}

void	create_bvh(t_world *world)

{
	int	i;

	if (!world)
		return ;
	new_group(&world->bvh[0]);
	new_group(&world->bvh[1]);
	new_group(&world->bvh[2]);
	i = -1;
	while (++i < world->objs_count)
		add_child(&world->bvh[0], &world->objs[i]);
	// world->bvh[0].bounds_of(&world->bvh[0]);
	// divide_tree(&world->bvh[0], &world->bvh[1], &world->bvh[2]);
	world->bvh[0].is_bounds_precal = false;
	// world->bvh[1].is_bounds_precal = false;
	// world->bvh[2].is_bounds_precal = false;
	world->bvh[0].bounds_of(&world->bvh[0]);
	// world->bvh[1].bounds_of(&world->bvh[1]);
	// world->bvh[2].bounds_of(&world->bvh[2]);
}
