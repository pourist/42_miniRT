#include "obj_loader.h"

bool	parse_transparency_texture(t_mtl_loader *loader, t_material *mtl,
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
	mtl->pattern.texture[3] = mlx_load_png(file_path);
	if (!mtl->pattern.texture[3])
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)),
			free(file_path), false);
	free(file_path);
	file_path = NULL;
	return (true);
}

bool	parse_bump_texture(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	char	*file_path;

	file_path = NULL;
	if (!params[1] || (params[2] && !is_float(params[2]))
		|| (params[2] && !params[3]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	if (ft_strncmp(params[1], "-bm", 4) == 0)
	{
		mtl->pattern.bump_map_scale = ft_atof(params[2]);
		if (mtl->pattern.bump_map_scale <= 0)
			mtl->pattern.bump_map_scale = 0.1;
		file_path = ft_strjoin(TEXTURE_PATH, params[3]);
	}
	else
		file_path = ft_strjoin(TEXTURE_PATH, params[1]);
	mtl->pattern.texture[4] = mlx_load_png(file_path);
	if (!mtl->pattern.texture[4])
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)),
			free(file_path), false);
	free(file_path);
	return (true);
}

bool	parse_reflection_texture(t_mtl_loader *loader, t_material *mtl,
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
	mtl->pattern.texture[5] = mlx_load_png(file_path);
	if (!mtl->pattern.texture[5])
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)),
			free(file_path), false);
	free(file_path);
	file_path = NULL;
	return (true);
}

bool	parse_ambient_texture(t_mtl_loader *loader, t_material *mtl,
		char **params, int *line_nb)
{
	char	*file_path;

	file_path = NULL;
	if (!params[1] || (params[2] && !is_float(params[2]))
		|| (params[2] && !params[3]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	file_path = ft_strjoin(TEXTURE_PATH, params[1]);
	mtl->pattern.texture[6] = mlx_load_png(file_path);
	if (!mtl->pattern.texture[6])
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)),
			free(file_path), false);
	free(file_path);
	file_path = NULL;
	return (true);
}

bool	parse_displacement_texture(t_mtl_loader *loader, t_material *mtl,
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
	if (ft_strncmp(params[1], "-d", 3) == 0)
	{
		mtl->pattern.disp_intensity = ft_atof(params[2]);
		if (mtl->pattern.disp_intensity <= 0)
			mtl->pattern.disp_intensity = 0.1;
		file_path = ft_strjoin(TEXTURE_PATH, params[3]);
	}
	else
		file_path = ft_strjoin(TEXTURE_PATH, params[1]);
	mtl->pattern.texture[7] = mlx_load_png(file_path);
	if (!mtl->pattern.texture[7])
		return (printf("minirt: %s\n", mlx_strerror(mlx_errno)),
			free(file_path), false);
	free(file_path);
	return (true);
}
