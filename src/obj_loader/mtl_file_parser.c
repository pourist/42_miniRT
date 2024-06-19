#include "obj_loader.h"

static void	free_materials(t_mtl_loader *mtl)
{
	int	i;

	i = -1;
	while (++i < mtl->m_count)
		mlx_delete_texture(mtl->materials[i].pattern.texture[0]);
	free(mtl->materials);
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
	free_3d_array(loader->tokens);
	return (true);
}

static bool	split_in_tokens(t_mtl_loader *mtl, int *nb_lines)
{
	int	i;

	i = -1;
	while (++i < *nb_lines)
	{
		mtl->tokens[i] = ft_subsplit(mtl->lines[i], " \n");
		if (!mtl->tokens[i])
			return (perror("minirt: split_in_tokens: malloc"),
				free_matrix(mtl->lines), false);
		if (ft_strncmp(mtl->tokens[i][0], "newmtl", 7) == 0)
			mtl->m_max++;
	}
	mtl->materials = (t_material *)malloc(mtl->m_max * sizeof(t_material));
	free_matrix(mtl->lines);
	mtl->lines = NULL;
	return (true);
}

bool	load_mtl_files(t_obj_loader *loader, int *nb_iters)
{
	int				i;
	int				nb_lines;
	char			*file_content;
	t_mtl_loader	*mtl; 

	i = -1;
	file_content = NULL;
	while (++i < *nb_iters)
	{
		if (ft_strncmp(loader->tokens[i][0], "mtllib", 7) == 0)
		{
			mtl = &loader->mtl_loader[loader->mtl_count++];
			mtl->filename = loader->tokens[i][1];
			if (!read_file_to_memory(mtl->filename, &file_content, false))
				return (free(file_content), false);
			if (!split_file_in_lines(&file_content, &mtl->lines,
					&mtl->tokens, &nb_lines))
				return (free(file_content), free_matrix(mtl->lines), false);
			if (!split_in_tokens(mtl, &nb_lines))
				return (free_3d_array(mtl->tokens), false);
			if (!create_materials(mtl))
				return (free_3d_array(mtl->tokens), false);
		}
	}
	return (true);
}
