#include "obj_loader.h"

static void	free_materials(t_mtl_loader *mtl)
{
	int	i;

	i = -1;
	while (++i < mtl->m_count)
	{
		if (mtl->materials[i].pattern.texture[0])
		{
			mlx_delete_texture(mtl->materials[i].pattern.texture[0]);
			mtl->materials[i].pattern.texture[0] = NULL;
		}
	}
	free(mtl->materials);
	mtl->materials = NULL;
}

static bool	create_materials(t_mtl_loader *loader)
{
	int	i;

	i = -1;
	while (loader->tokens[++i])
	{
		if (!mtl_parse_line(loader, loader->tokens[i], i + 1))
			return (free_materials(loader), false);
	}
	loader->m_count = 0;
	loader->current_mtl = &loader->materials[loader->m_count];
	return (true);
}

static bool	split_in_tokens(t_mtl_loader *mtl, int *nb_lines)
{
	int	i;

	i = -1;
	while (++i < *nb_lines)
	{
		mtl->tokens[i] = ft_subsplit(mtl->lines[i], " \r\n\t");
		if (!mtl->tokens[i])
			return (perror("minirt: split_in_tokens: malloc"),
				free_matrix(mtl->lines), false);
		if (ft_strncmp(mtl->tokens[i][0], "newmtl", 7) == 0)
			mtl->m_max++;
	}
	mtl->materials = (t_material *)ft_calloc(mtl->m_max, sizeof(t_material));
	free_matrix(mtl->lines);
	mtl->lines = NULL;
	return (true);
}

bool	mtl_file_parser(t_mtl_loader *mtl)
{
	char			*file_content;
	int				nb_lines;

	file_content = NULL;
	if (!read_file_to_memory(mtl->filename, &file_content, false))
		return (free(file_content), false);
	if (!split_file_in_lines(&file_content, &mtl->lines,
			&mtl->tokens, &nb_lines))
		return (free(file_content), false);
	if (!split_in_tokens(mtl, &nb_lines))
		return (false);
	if (!create_materials(mtl))
		return (false);
	return (true);
}

bool	load_mtl_files(t_obj_loader *loader, int *nb_iters)
{
	int				i;
	t_mtl_loader	*mtl; 

	i = -1;
	while (++i < *nb_iters)
	{
		if (loader->tokens[i] && loader->tokens[i][0]
			&& ft_strncmp(loader->tokens[i][0], "mtllib", 7) == 0)
		{
			mtl = &loader->mtl_loader[loader->mtl_count++];
			if (loader->tokens[i][1] && loader->tokens[i][2])
				mtl->filename = ft_strjoin(MTL_PATH, loader->tokens[i][2]);
			else
				mtl->filename = ft_strjoin(MTL_PATH, loader->tokens[i][1]);
			if (!mtl_file_parser(mtl))
				return (false);
		}
	}
	loader->mtl_count = 0;
	return (true);
}
