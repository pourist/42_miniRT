#include "obj_loader.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix[i]);
	matrix[i] = NULL;
	free(matrix);
	matrix = NULL;
}

void	free_3d_array(char ***array)
{
	int	i;

	i = -1;
	while (array && array[++i])
	{
		free_matrix(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void	free_mtl_loader(t_obj_loader *loader)
{
	int	i;

	i = -1;
	if (!loader)
		return ;
	while (++i < loader->mtl_count)
	{
		if (loader->mtl_loader[i].filename)
			free(loader->mtl_loader[i].filename);
		if (loader->mtl_loader[i].lines)
			free_matrix(loader->mtl_loader[i].lines);
		if (loader->mtl_loader[i].tokens)
			free_3d_array(loader->mtl_loader[i].tokens);
		if (loader->mtl_loader[i].materials)
			free(loader->mtl_loader[i].materials);
	}
	if (loader->mtl_loader)
	{
		free(loader->mtl_loader);
		loader->mtl_loader = NULL;
	}
}

static void	free_loader2(t_obj_loader *loader)
{
	if (loader->vertices)
	{
		free(loader->vertices);
		loader->vertices = NULL;
	}
	if (loader->normals)
	{
		free(loader->normals);
		loader->normals = NULL;
	}
	if (loader->uvs)
	{
		free(loader->uvs);
		loader->uvs = NULL;
	}
	if (loader->mtl_loader)
		free_mtl_loader(loader);
}

void	free_loader(t_obj_loader *loader)
{
	if (!loader)
		return ;
	if (loader->filename)
	{
		free(loader->filename);
		loader->filename = NULL;
	}
	if (loader->lines)
	{
		free_matrix(loader->lines);
		loader->lines = NULL;
	}
	if (loader->tokens)
	{
		free_3d_array(loader->tokens);
		loader->tokens = NULL;
	}
	free_loader2(loader);
}
