#include "groups.h"

// static bool	compare_shapes(t_shape *a, t_shape *b)
// {
// 	double	center_a_x;
// 	double	center_b_x;

// 	if (!a->is_bounds_precal)
// 		a->bounds_of(a);
// 	if (!b->is_bounds_precal)
// 		b->bounds_of(b);
// 	center_b_x = (b->bounds.min.x + b->bounds.max.x) * 0.5;
// 	center_a_x = (a->bounds.min.x + a->bounds.max.x) * 0.5;
// 	return (center_a_x < center_b_x);
// }

// void	btree_insert(t_shape **root, t_shape *shape)
// {
// 	if (!root || !(*root))
// 	{
// 		if (root)
// 			(*root) = shape;
// 		return ;
// 	}
// 	if (compare_shapes(*root, shape))
// 	{
// 		if ((*root)->right)
// 			btree_insert(&(*root)->right, shape);
// 		else
// 			(*root)->right = shape;
// 	}
// 	else
// 	{
// 		if ((*root)->left)
// 			btree_insert(&(*root)->left, shape);
// 		else
// 			(*root)->left = shape;
// 	}
// }

double	volume(t_shape	*shape)
{
	if (shape)
	{
		if (!shape->is_bounds_precal)
			shape->bounds_of(shape);
		return ((shape->bounds.max.x - shape->bounds.min.x)
			* (shape->bounds.max.y - shape->bounds.min.y)
			* (shape->bounds.max.z - shape->bounds.min.z));
	}
	return (0);
}

t_shape	*select_root(t_shape *current, t_shape *shape)
{
	double	current_volume;
	double	shape_volume;

	current_volume = volume(current);
	shape_volume = volume(shape);
	if (shape_volume > current_volume)
		return (shape);
	return (current);
}

void	btree_insert(t_shape **root, t_shape *shape)
{
	t_shape	*current;

	if (!shape)
		return ;
	if (!root || !(*root))
	{
		if (root)
			(*root) = shape;
		return ;
	}
	current = *root;
	if (!current->is_bounds_precal || (current->left && current->right))
		current->bounds_of(current);
	if (!shape->is_bounds_precal || (shape->left && shape->right))
		shape->bounds_of(shape);
	if (box_contains_box(&current->split_box[0], &shape->bounds))
		btree_insert(&current->left, shape);
	else if (box_contains_box(&current->split_box[1], &shape->bounds))
		btree_insert(&current->right, shape);
	else
	{
		current = select_root(*root, shape);
		if (current == shape)
		{
			current = *root;
			*root = shape;
			(*root)->is_bounds_precal = false;
			btree_insert(root, current);
		}
		else
		{
			if (current->left)
				current->left->is_bounds_precal = false;
			btree_insert(&current->left, shape);
		}
	}
	(*root)->bounds_of((*root));
}

void	add_child(t_shape *group, t_shape *child)
{
	t_shape	*current;

	if (!group || !child)
		return ;
	if (!child->parent)
		child->parent = group;
	if (!group->is_bounds_precal || (group->left && group->right))
		group->bounds_of(group);
	if (!child->is_bounds_precal || (child->left && child->right))
		child->bounds_of(child);
	if (box_contains_box(&group->split_box[0], &child->bounds))
		btree_insert(&group->left, child);
	else if (box_contains_box(&group->split_box[1], &child->bounds))
		btree_insert(&group->right, child);
	else
	{
		current = select_root(group->left, group->right);
		if (current == group->right)
		{
			if (group->right)
				group->right->is_bounds_precal = false;
			btree_insert(&group->right, child);
		}
		else
		{
			if (group->left)
				group->left->is_bounds_precal = false;
			btree_insert(&group->left, child);
		}
	}
	group->is_bounds_precal = false;
	group->bounds_of(group);
}

void	get_group_bounds(t_shape *root, t_bounds *b)
{
	if (root)
	{
		if (!root->is_bounds_precal)
			root->bounds_of(root);
		if (root->bounds.min.x < b->min.x)
			b->min.x = root->bounds.min.x;
		if (root->bounds.min.y < b->min.y)
			b->min.y = root->bounds.min.y;
		if (root->bounds.min.z < b->min.z)
			b->min.z = root->bounds.min.z;
		if (root->bounds.max.x > b->max.x)
			b->max.x = root->bounds.max.x;
		if (root->bounds.max.y > b->max.y)
			b->max.y = root->bounds.max.y;
		if (root->bounds.max.z > b->max.z)
			b->max.z = root->bounds.max.z;
		if (root->left)
			get_group_bounds(root->left, b);
		if (root->right)
			get_group_bounds(root->right, b);
	}
}

void	intersect_group_shapes(t_shape *root, t_hit **xs, t_ray *r)
{
	if (root)
	{
		// if (intersect_bounds(&root->split_box[0], r) && root->left)
		// 	intersect_group_shapes(root->left, xs, r);
		// if (intersect_bounds(&root->split_box[1], r) && root->right)
		// 	intersect_group_shapes(root->right, xs, r);
		if (root->left)
			intersect_group_shapes(root->left, xs, r);
		if (root->right)
			intersect_group_shapes(root->right, xs, r);
		intersect(xs, root, r);
	}
}
