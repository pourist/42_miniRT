#include "obj_loader.h"

static bool	parse_ambient(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	new_color(ft_atof(params[1]), ft_atof(params[2]), ft_atof(params[3]),
		&mtl->ambient);
	return (true);
}

static bool	parse_diffuse(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	mtl->diffuse = (ft_atof(params[1]) + ft_atof(params[2])
			+ ft_atof(params[3])) / 3;
	return (true);
}

static bool	parse_specular(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	mtl->specular = (ft_atof(params[1]) + ft_atof(params[2])
			+ ft_atof(params[3])) / 3;
	return (true);
}

static bool	mtl_parse_file2(t_mtl_loader *loader, char const *filename)
{
	if ((ft_strncmp(params[0], "d", type_size) == 0)
		|| (ft_strncmp(params[0], "Tr", type_size) == 0))
		return (parse_transparency(loader, loader->current_mtl,
				params, &line_nb));
	else if (ft_strncmp(params[0], "map_bump", type_size) == 0)
		return (parse_bump_texture(loader, loader->current_mtl, params,
				&line_nb));
	print_ignore_message(loader->filename, &line_nb);
	loader->ignored_lines++;
	return (true);
}

bool	mtl_parse_line(t_mtl_loader *loader, char **params, int line_nb)
{
	int	type_size;

	if (!params[0])
	{
		print_ignore_message(loader->filename, &line_nb);
		loader->ignored_lines++;
		return (true);
	}
	type_size = ft_strlen(params[0]) + 1;
	if (ft_strncmp(params[0], "newmtl", type_size) == 0)
		loader->current_mtl = &loader->materials[loader->m_count++];
	else if (ft_strncmp(params[0], "Ka", type_size) == 0)
		return (parse_ambient(loader, loader->current_mtl, params, &line_nb));
	else if (ft_strncmp(params[0], "Kd", type_size) == 0)
		return (parse_diffuse(loader, loader->current_mtl, params, &line_nb));
	else if (ft_strncmp(params[0], "Ks", type_size) == 0)
		return (parse_specular(loader, loader->current_mtl, params, &line_nb));
	else if (ft_strncmp(params[0], "Ns", type_size) == 0)
		return (parse_shininess(loader, loader->current_mtl, params, &line_nb));
	else if (ft_strncmp(params[0], "map_Kd", type_size) == 0)
		return (parse_texture(loader, loader->current_mtl, params, &line_nb));
	else
		return (mtl_parse_line2(loader, params, line_nb));
}
