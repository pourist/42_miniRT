#include "obj_loader.h"

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

bool	parse_diffuse_texture(t_mtl_loader *loader, t_material *mtl,
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

bool	parse_specular_texture(t_mtl_loader *loader, t_material *mtl,
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
	mtl->pattern.texture[1] = mlx_load_png(file_path);
	if (!mtl->pattern.texture[1])
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)),
			free(file_path), false);
	free(file_path);
	file_path = NULL;
	return (true);
}

bool	parse_shininess_texture(t_mtl_loader *loader, t_material *mtl,
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
	mtl->pattern.texture[2] = mlx_load_png(file_path);
	if (!mtl->pattern.texture[2])
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)),
			free(file_path), false);
	free(file_path);
	file_path = NULL;
	return (true);
}
