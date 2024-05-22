#include "utils.h"
#include "world.h"

static void	free_pattern(t_pattern *pattern)
{
	if (pattern->has_pattern)
	{
		free(pattern->a);
		free(pattern->b);
	}
}

static void	free_group(t_shape *root)
{
	t_shape	*tmp;

	while (root)
	{
		if (root->is_group)
			free_group(root->root);
		free_pattern(&root->material.pattern);
		tmp = root;
		root = tmp->next;
		free(tmp);
	}
}

void	free_world(t_world *world)
{
	int		i;

	i = -1;
	while (++i < world->objs_count)
	{
		free_pattern(&world->objs[i].material.pattern);
		if (world->objs[i].is_group)
			free_group(world->objs[i].root);
	}
	free(world->lights);
	free(world->objs);
}
