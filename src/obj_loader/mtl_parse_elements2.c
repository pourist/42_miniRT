#include "obj_loader.h"

bool	parse_texture(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	char	*file_path;

	file_path = NULL;
	if (!params[1] || params[2])
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	file_path = ft_strjoin(TEXTURE_PATH, params[1]);
	if (!new_triangular_texture_map(&mtl->pattern, file_path))
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)),
			free(file_path), false);
	free(file_path);
	file_path = NULL;
	return (true);
}

bool	parse_transparency(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	if (!params[1] || params[2] || !is_float(params[1]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	mtl->transparency = ft_atof(params[1]);
	return (true);
}

bool	parse_bump_texture(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	int	i;

	if (!params[1] || params[2])
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	i = 0;
	while (i < 6 && mtl->pattern.texture[i])
		++i;
	mtl->pattern.texture[i] = mlx_load_png(params[1]);
	if (!mtl->pattern.texture[i])
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)), false);
	return (true);
}

bool	parse_refractive_i(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	if (!params[1] || params[2] || !is_float(params[1]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	mtl->refractive_index = ft_atof(params[1]);
	return (true);
}
