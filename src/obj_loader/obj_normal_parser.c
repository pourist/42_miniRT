#include "obj_loader.h"

bool	parse_normal(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
		return (loader->ignored_lines++, print_ignore_message(*line_nb));
	if (loader->n_count == loader->n_max)
	{
		loader->n_max++;
		loader->normals = ft_realloc(loader->normals,
				loader->n_max * sizeof(t_point));
		if (!loader->normals)
			return (false);
	}
	loader->normals[loader->n_count] = new_point(ft_atof(params[1]),
			ft_atof(params[2]), ft_atof(params[3]));
	loader->n_count++;
	return (true);
}
