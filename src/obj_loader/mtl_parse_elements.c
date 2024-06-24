#include "obj_loader.h"

bool	parse_newmtl(t_mtl_loader *loader)
{
	if (loader->m_count < loader->m_max)
	{
		loader->current_mtl = &loader->materials[loader->m_count++];
		new_material(loader->current_mtl);
		return (true);
	}
	return (false);
}

bool	parse_ambient(t_mtl_loader *loader, t_material *mtl,
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

bool	parse_diffuse(t_mtl_loader *loader, t_material *mtl,
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

bool	parse_specular(t_mtl_loader *loader, t_material *mtl,
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

bool	parse_shininess(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	if (!params[1] || params[2] || !is_float(params[1]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	mtl->shininess = ft_atof(params[1]);
	return (true);
}
