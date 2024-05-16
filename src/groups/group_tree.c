#include "shapes.h"

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
