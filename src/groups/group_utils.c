#include "groups.h"

static t_group	*new_node(t_shape *shape)
{
	static t_group	pool[MAX_NODES + 1];
	static size_t	index = 0;
	t_group			*node;

	node = &pool[index++ & (MAX_NODES)];
	node->shape = shape;
	node->next = NULL;
	return (node);
}

void	insert_node(t_group **root, t_group *child)
{
	t_group	*current;

	if (*root == NULL)
		*root = child;
	else
	{
		current = *root;
		while (current->next)
			current = current->next;
		current->next = child;
	}
}

void	add_child(t_shape *group, t_shape *child)
{
	if (!group || !child)
		return ;
	child->parent = group;
	if (!group->g)
		group->g = new_node(child);
	else
		insert_node(&group->g, new_node(child));
}

void	get_group_bounds(t_group **root, t_bounds *b)
{
	t_group	*current;

	current = *root;
	while (current)
	{
		if (current->shape)
		{
			if (!current->shape->is_bounds_precal)
				current->shape->bounds_fn(current->shape);
			if (current->shape->bounds.min.x < b->min.x)
				b->min.x = current->shape->bounds.min.x;
			if (current->shape->bounds.min.y < b->min.y)
				b->min.y = current->shape->bounds.min.y;
			if (current->shape->bounds.min.z < b->min.z)
				b->min.z = current->shape->bounds.min.z;
			if (current->shape->bounds.max.x > b->max.x)
				b->max.x = current->shape->bounds.max.x;
			if (current->shape->bounds.max.y > b->max.y)
				b->max.y = current->shape->bounds.max.y;
			if (current->shape->bounds.max.z > b->max.z)
				b->max.z = current->shape->bounds.max.z;
		}
		current = current->next;
	}
}

void	intersect_group_shapes(t_group **root, t_hit **xs, t_ray *r)
{
	t_group	*current;

	current = *root;
	while (current)
	{
		if (current->shape)
			intersect(xs, current->shape, *r);
		current = current->next;
	}
}
