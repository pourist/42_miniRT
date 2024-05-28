#include "obj_loader.h"

bool	parse_group(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1])
		return (loader->ignored_lines++, print_ignore_message(*line_nb));
	if (loader->g_count == loader->g_max)
	{
		loader->g_max++;
		loader->groups = ft_realloc(loader->groups,
				loader->g_max * sizeof(t_shape));
		if (!loader->groups)
			return (false);
	}
	new_group(&loader->groups[loader->g_count]);
	loader->current_g = &loader->groups[loader->g_count];
	add_child(&loader->default_group, loader->current_g);
	loader->g_count++;
	return (true);
}
