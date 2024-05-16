#include "shapes.h"

t_shape	new_group(void)
{
	t_shape	shape; 

	shape = new_shape();
	shape.g = NULL;
	// shape.intersect_fn = intersect_group;
	// shape.normal_at = normal_at_group;
	return (shape);
}

t_group	*new_node(t_shape *shape)
{
	static t_group	pool[MAX_NODES + 1];
	static size_t	index = 0;
	t_group			*node;

	node = &pool[index++ & (MAX_NODES)];
	node->shape = *shape;
	node->right = NULL;
	node->left = NULL;
	node->parent = NULL;
	return (node);
}

void	add_child(t_shape *group, t_shape *child)
{
	t_group	*left;
	t_group	*right;

	child->parent = group;
	if (group->g == NULL)
		group->g = new_node(child);
	else
	{
		left = group->g;
		right = group->g;
		while (right->right != NULL)
		{
			left = right;
			right = right->right;
		}
		right->right = new_node(child);
		right->left = left;
	}
}
