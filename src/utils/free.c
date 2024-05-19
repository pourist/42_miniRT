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

static void	free_group(t_group *group)
{
	while (group)
	{
		if (group->shape->is_group)
			free_group(group->shape->g);
		free_pattern(&group->shape->material.pattern);
		free(group->shape);
		group = group->next;
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
			free_group(world->objs[i].g);
	}
	free(world->lights);
	free(world->objs);
}
