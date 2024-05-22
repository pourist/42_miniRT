#include "obj_loader.h"

static void	read_face(t_obj_loader *loader, char **params)
{
	int		p_len;

	p_len = ft_matrix_len(params) - 1;
	if (p_len < 3)
		return ;
	else if (p_len > 3)
		loader->t_max += p_len - 2;
	else
		loader->t_max++;
}

static void	read_line(t_obj_loader *loader, char **params)
{
	int	type_size;

	if (!params[0])
		return ;
	type_size = ft_strlen(params[0]) + 1;
	if (ft_strncmp(params[0], "v", type_size) == 0)
		loader->v_max++;
	else if (ft_strncmp(params[0], "vn", type_size) == 0)
		loader->n_max++;
	else if (ft_strncmp(params[0], "f", type_size) == 0)
		read_face(loader, params);
	else if (ft_strncmp(params[0], "g", type_size) == 0)
		loader->g_max++;
}

bool	set_max_values(t_obj_loader *loader, char *filename)
{
	int		fd;
	char	*line;
	char	**params;

	if (!open_obj_file(filename, &fd))
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		params = ft_subsplit(line, " \n");
		read_line(loader, params);
		free(line);
		free_array(params);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	loader->normals = malloc(loader->n_max * sizeof(t_vector));
	loader->groups = malloc(loader->g_max * sizeof(t_shape));
	loader->vertices = malloc(loader->v_max * sizeof(t_point));
	loader->triangles = malloc(loader->t_max * sizeof(t_shape));
	if (!loader->normals || !loader->groups || !loader->vertices
		|| !loader->triangles)
		return (false);
	return (true);
}
