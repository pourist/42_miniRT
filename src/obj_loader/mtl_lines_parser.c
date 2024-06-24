#include "obj_loader.h"

static bool	mtl_parse_line2(t_mtl_loader *ld, char **params,
		int *line_nb, int *type_size)
{
	if ((ft_strncmp(params[0], "d", *type_size) == 0)
		|| (ft_strncmp(params[0], "Tr", *type_size) == 0))
		return (parse_transparency(ld, ld->current_mtl, params, line_nb));
	else if (ft_strncmp(params[0], "map_Kd", *type_size) == 0)
		return (parse_diffuse_texture(ld, ld->current_mtl, params, line_nb));
	else if (ft_strncmp(params[0], "map_ks", *type_size) == 0)
		return (parse_specular_texture(ld, ld->current_mtl, params, line_nb));
	else if (ft_strncmp(params[0], "map_Ns", *type_size) == 0)
		return (parse_shininess_texture(ld, ld->current_mtl, params, line_nb));
	else if (ft_strncmp(params[0], "map_d", *type_size) == 0)
		return (parse_transparency_texture(ld, ld->current_mtl, params,
				line_nb));
	else if (ft_strncmp(params[0], "map_Bump", *type_size) == 0 || ft_strncmp(
			params[0], "map_bump", *type_size) == 0)
		return (parse_bump_texture(ld, ld->current_mtl, params, line_nb));
	else if (ft_strncmp(params[0], "map_refl", *type_size) == 0)
		return (parse_reflection_texture(ld, ld->current_mtl, params, line_nb));
	else if (ft_strncmp(params[0], "map_Ka", *type_size) == 0)
		return (parse_ambient_texture(ld, ld->current_mtl, params, line_nb));
	else if (ft_strncmp(params[0], "disp", *type_size) == 0)
		return (parse_displacement_texture(ld, ld->current_mtl, params,
				line_nb));
	print_ignore_message(ld->filename, line_nb);
	ld->ignored_lines++;
	return (true);
}

bool	mtl_parse_line(t_mtl_loader *ld, char **params, int line_nb)
{
	int	type_size;

	if (params[0])
	{
		type_size = ft_strlen(params[0]) + 1;
		if (ft_strncmp(params[0], "newmtl", type_size) == 0)
			return (parse_newmtl(ld));
		else if (ft_strncmp(params[0], "Ka", type_size) == 0)
			return (parse_ambient(ld, ld->current_mtl, params, &line_nb));
		else if (ft_strncmp(params[0], "Kd", type_size) == 0)
			return (parse_diffuse(ld, ld->current_mtl, params, &line_nb));
		else if (ft_strncmp(params[0], "Ks", type_size) == 0)
			return (parse_specular(ld, ld->current_mtl, params, &line_nb));
		else if (ft_strncmp(params[0], "Ni", type_size) == 0)
			return (parse_refractive_i(ld, ld->current_mtl, params, &line_nb));
		else if (ft_strncmp(params[0], "Ns", type_size) == 0)
			return (parse_shininess(ld, ld->current_mtl, params, &line_nb));
		else
			return (mtl_parse_line2(ld, params, &line_nb, &type_size));
	}
	print_ignore_message(ld->filename, &line_nb);
	ld->ignored_lines++;
	return (true);
}
