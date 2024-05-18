#include "groups.h"

static t_group	*new_node(t_shape *shape)
{
	static t_group	pool[MAX_NODES + 1];
	static size_t	index = 0;
	t_group			*node;

	node = &pool[index++ & (MAX_NODES)];
	node->shape = shape;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

static void	insert_node(t_group *root, t_shape *child)
{
	while (root)
	{
		if (root->shape < child)
		{
			if (root->left)
				root = root->left;
			else
			{
				root->left = new_node(child);
				return ;
			}
		}
		else
		{
			if (root->right)
				root = root->right;
			else
			{
				root->right = new_node(child);
				return ;
			}
		}
	}
}

void	add_child(t_shape *group, t_shape *child)
{
	if (!group)
		return ;
	child->parent = group;
	if (!group->g)
	{
		group->g = new_node(child);
		return ;
	}
	insert_node(group->g, child);
}

void	get_group_max_bounds(t_group *root, t_bounds *b)
{
	if (root)
	{
		if (root->left)
			get_group_max_bounds(root->left, b);
		if (root->right)
			get_group_max_bounds(root->right, b);
		if (!root->shape->is_bounds_precal)
			root->shape->bounds_fn(root->shape);
		if (root->shape->bounds.min.x < b->min.x)
			b->min.x = root->shape->bounds.min.x;
		if (root->shape->bounds.min.y < b->min.y)
			b->min.y = root->shape->bounds.min.y;
		if (root->shape->bounds.min.z < b->min.z)
			b->min.z = root->shape->bounds.min.z;
		if (root->shape->bounds.max.x > b->max.x)
			b->max.x = root->shape->bounds.max.x;
		if (root->shape->bounds.max.y > b->max.y)
			b->max.y = root->shape->bounds.max.y;
		if (root->shape->bounds.max.z > b->max.z)
			b->max.z = root->shape->bounds.max.z;
	}
}

void	intersect_btree_prefix(t_group *root, t_hit **xs, t_ray *r)
{
	if (root)
	{
		intersect(xs, root->shape, *r);
		if (root->left)
			intersect_btree_prefix(root->left, xs, r);
		if (root->right)
			intersect_btree_prefix(root->right, xs, r);
	}
}
