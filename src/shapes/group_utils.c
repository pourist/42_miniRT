#include "groups.h"

double	volume(t_shape	*shape)
{
	if (shape)
	{
		if (!shape->is_bounds_precal)
			shape->bounds_of(shape);
		return ((shape->subg_bounds.max.x - shape->subg_bounds.min.x)
			* (shape->subg_bounds.max.y - shape->subg_bounds.min.y)
			* (shape->subg_bounds.max.z - shape->subg_bounds.min.z));
	}
	return (0);
}

t_shape	*select_root(t_shape *current, t_shape *shape)
{
	double	current_volume;
	double	shape_volume;

	if (!current)
		return (current);
	if (!shape)
		return (shape);
	current_volume = volume(current);
	shape_volume = volume(shape);
	if (shape_volume > current_volume)
		return (shape);
	return (current);
}

void	btree_insert(t_shape **root, t_shape *shape)
{
	t_shape	*current;

	if (!root || !(*root))
	{
		if (root)
			(*root) = shape;
		return ;
	}
	current = *root;
	if (!current->is_bounds_precal)
		current->bounds_of(current);
	if (!shape->is_bounds_precal)
		shape->bounds_of(shape);
	if (box_contains_box(&current->split_box[0], &shape->subg_bounds))
		btree_insert(&current->left, shape);
	else
		btree_insert(&current->right, shape);
	// else if (box_contains_box(&current->split_box[1], &shape->subg_bounds))
	// 	btree_insert(&current->right, shape);
	// else
	// {
	// 	if (current->right == select_root(current->left, current->right))
	// 		btree_insert(&current->right, shape);
	// 	else
	// 		btree_insert(&current->left, shape);
	// }
	current->is_bounds_precal = false;
}

void	add_child(t_shape *group, t_shape *child)
{
	// t_shape	*tmp;

	if (!group || !child)
		return ;
	if (!child->parent)
		child->parent = group;
	if (!group->is_bounds_precal)
		group->bounds_of(group);
	if (!child->is_bounds_precal)
		child->bounds_of(child);
	if (!group->root)
		group->root = child;
	else if (box_contains_box(&group->split_box[0], &child->bounds))
		btree_insert(&group->root->left, child);
	else
		btree_insert(&group->root->right, child);
	// else if (box_contains_box(&group->split_box[1], &child->bounds))
	// 	btree_insert(&group->root->right, child);
	// else
	// {
	// 	tmp = group->root;
	// 	group->root = child;
	// 	group->root->left = tmp;
	// 	btree_insert(&group->root, tmp);
	// }
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
		// if (root->left && intersect_bounds(&root->left->subg_bounds, r))
		// 	intersect_group_shapes(root->left, xs, r);
		// if (root->right && intersect_bounds(&root->right->subg_bounds, r))
		// 	intersect_group_shapes(root->right, xs, r);
		if (root->is_bounds_precal)
			root->bounds_of(root);
		if (intersect_bounds(&root->subg_bounds, r))
		{
			// if (root->left)
			// 	intersect_group_shapes(root->left, xs, r);
			// else if (root->right)
			// 	intersect_group_shapes(root->right, xs, r);
			if (root->left && intersect_bounds(&root->left->subg_bounds, r))
				intersect_group_shapes(root->left, xs, r);
			if (root->right && intersect_bounds(&root->right->subg_bounds, r))
				intersect_group_shapes(root->right, xs, r);
			if (intersect_bounds(&root->subg_bounds, r))
				intersect(xs, root, r);
		}
	}
}
