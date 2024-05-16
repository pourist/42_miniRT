#include "shapes.h"

static bool	intersect_group(t_hit **xs, t_shape *group, t_ray r);

t_shape	new_group(void)
{
	t_shape	shape; 

	shape = new_shape();
	shape.g = NULL;
	shape.intersect_fn = intersect_group;
	// shape.normal_at = normal_at_group;
	return (shape);
}

static void	intersect_btree_prefix(t_group *root, t_hit **xs, t_ray *r)
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

static bool	intersect_group(t_hit **xs, t_shape *group, t_ray r)
{
	t_group	*group_tree; 

	group_tree = group->g;
	intersect_btree_prefix(group_tree, xs, &r);
	return (intersect_count(*xs) > 0);
}

t_point	world_to_object(t_shape *shape, t_point world_point)
{
	if (shape->parent)
		world_point = world_to_object(shape->parent, world_point);
	return (multiply_matrix_by_tuple(shape->inverse, world_point));
}
