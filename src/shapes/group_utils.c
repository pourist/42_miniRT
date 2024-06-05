#include "groups.h"

void	add_child(t_shape *group, t_shape *child)
{
	t_shape	*current;

	if (!group || !child)
		return ;
	if (!child->parent)
		child->parent = group;
	if (!group->is_bounds_precal || !group->is_gbounds_precal)
		group->bounds_of(group);
	if (!child->is_bounds_precal || !child->is_gbounds_precal)
		child->bounds_of(child);
	current = group->root;
	while (current->next)
	{
		current->is_gbounds_precal = false;
		current = current->next;
	}
	current->next = child;
	group->is_gbounds_precal = false;
	group->is_bounds_precal = false;
	group->bounds_of(group);
}

void	get_group_bounds(t_shape *root, t_bounds *b)
{
	while (root)
	{
		if (!root->is_bounds_precal || !root->is_gbounds_precal)
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
		root = root->next;
	}
}

void	intersect_group_shapes(t_shape **root, t_hit **xs, t_ray *r)
{
	// t_shape	*current;

	// current = *root;
	// while (current)
	// {
	// 	if (current && (!current->is_bounds_precal || !current->is_gbounds_precal))
	// 		current->bounds_of(current);
	// 	if (intersect_bounds(&current->bounds, r))
	// 		intersect(xs, current, r);
	// 	if (!intersect_bounds(&current->subg_bounds, r))
	// 		break ;
	// 	current = current->next;
	// }
	t_shape	*current;

	current = *root;
	while (current)
	{
		intersect(xs, current, r);
		current = current->next;
	}
}
