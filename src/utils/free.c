#include "utils.h"
#include "world.h"

static void	free_csg(t_shape *csg);

static void	free_pattern(t_pattern *pattern)
{
	if (pattern->has_pattern)
	{
		if (pattern->a)
			free(pattern->a);
		if (pattern->b)
			free(pattern->b);
	}
}

static void	free_group(t_shape *root)
{
	if (root)
	{
		if (root->left)
		{
			free_group(root->left);
			root->left = NULL;
		}
		if (root->right)
		{
			free_group(root->right);
			root->right = NULL;
		}
		free_pattern(&root->material.pattern);
		free(root);
	}
}

static void	free_csg(t_shape *csg)
{
	if (csg)
	{
		if (csg->is_csg)
		{
			if (csg->csg.left)
				free_csg(csg->csg.left);
			csg->csg.left = NULL;
			if (csg->csg.right)
				free_csg(csg->csg.right);
			csg->csg.right = NULL;
		}
		if (csg->is_group && (csg->left || csg->right))
		{
			free_group(csg->left);
			free_group(csg->right);
			csg->left = NULL;
			csg->right = NULL;
		}
		free_pattern(&csg->material.pattern);
		free(csg);
	}
}

void	free_world(t_world *world)
{
	int		i;

	i = -1;
	while (++i < world->objs_count)
	{
		free_pattern(&world->objs[i].material.pattern);
		if (world->objs[i].is_group
			&& (world->objs[i].left || world->objs[i].right))
		{
			free_group(world->objs[i].left);
			free_group(world->objs[i].right);
			world->objs[i].left = NULL;
			world->objs[i].right = NULL;
		}
		if (world->objs[i].is_csg)
		{
			if (world->objs[i].csg.left)
				free_csg(world->objs[i].csg.left);
			world->objs[i].csg.left = NULL;
			if (world->objs[i].csg.right)
				free_csg(world->objs[i].csg.right);
			world->objs[i].csg.right = NULL;
		}
	}
	free(world->lights);
	free(world->objs);
}
