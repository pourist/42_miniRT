#include "obj_loader.h"

bool	parse_vertice(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
		return (loader->ignored_lines++, print_ignore_message(*line_nb));
	if (loader->v_count == loader->v_max)
	{
		loader->v_max++;
		loader->vertices = ft_realloc(loader->vertices,
				loader->v_max * sizeof(t_point));
		if (!loader->vertices)
			return (false);
	}
	new_point(ft_atof(params[1]), ft_atof(params[2]), ft_atof(params[3]),
		&loader->vertices[loader->v_count]);
	loader->v_count++;
	return (true);
}
