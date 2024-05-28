#include "groups.h"

void	add_child(t_shape *group, t_shape *child)
{
	t_shape	*current;

	if (!group || !child)
		return ;
	child->parent = group;
	if (!group->root)
		group->root = child;
	else
	{
		current = group->root;
		while (current->next)
			current = current->next;
		current->next = child;
	}
}

void	get_group_bounds(t_shape **root, t_bounds *b)
{
	t_shape	*current;

	current = *root;
	while (current)
	{
		if (!current->is_bounds_precal)
			current->bounds_fn(current);
		if (current->bounds.min.x < b->min.x)
			b->min.x = current->bounds.min.x;
		if (current->bounds.min.y < b->min.y)
			b->min.y = current->bounds.min.y;
		if (current->bounds.min.z < b->min.z)
			b->min.z = current->bounds.min.z;
		if (current->bounds.max.x > b->max.x)
			b->max.x = current->bounds.max.x;
		if (current->bounds.max.y > b->max.y)
			b->max.y = current->bounds.max.y;
		if (current->bounds.max.z > b->max.z)
			b->max.z = current->bounds.max.z;
		current = current->next;
	}
}

void	intersect_group_shapes(t_shape **root, t_hit **xs, t_ray *r)
{
	t_shape	*current;

	current = *root;
	while (current)
	{
		intersect(xs, current, *r);
		current = current->next;
	}
}
