#include "obj_loader.h"

t_obj_loader	new_obj_loader(void)
{
	return ((t_obj_loader){
		.ignored_lines = 0,
		.vertices = NULL,
		.vertices_count = 0,
		.vertices_max = 4,
		.normals = NULL,
		.normals_count = 0,
		.normals_max = 4,
		.triangles = NULL,
		.tri_count = 0,
		.tri_max = 1,
		.groups = NULL,
		.g_count = 0,
		.g_max = 1,
		.current_g = NULL
	});
}

bool	check_extension(char *filename, char *ext)
{
	char const	*file_ext;

	file_ext = ft_strrchr(filename, '.');
	if (file_ext)
	{
		if (ft_strncmp(file_ext, ext, ft_strlen(ext) + 1) == 0)
			return (true);
	}
	return (false);
}

static bool	open_obj_file(char *filename, int *fd)
{
	if (!check_extension(filename, ".obj"))
		return (ft_putendl_fd("minirt: Wrong file extension, .obj expected",
				STDERR_FILENO), false);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		return (ft_putstr_fd("minirt: ", STDERR_FILENO),
			perror(filename), false);
	return (true);
}

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

bool	is_float(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
			dot_count++;
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (false);
		i++;
	}
	if (dot_count > 1)
		return (false);
	return (true);
}

bool	are_floats(char *str1, char *str2, char *str3)
{
	if (!is_float(str1) || !is_float(str2) || !is_float(str3))
		return (false);
	return (true);
}

bool	parse_vertice(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
	{
		ft_putstr_fd("minirt: Wrong Vertice format on line ", STDERR_FILENO);
		ft_putnbr_fd(*line_nb, STDERR_FILENO);
		ft_putendl_fd(" (ignored).", STDERR_FILENO);
		return (false);
	}
	if (!loader->vertices || loader->vertices_count == loader->vertices_max)
	{
		loader->vertices_max *= 2;
		loader->vertices = ft_realloc(loader->vertices,
				loader->vertices_max * sizeof(t_point));
	}
	loader->vertices[loader->vertices_count] = new_point(ft_atof(params[1]),
			ft_atof(params[2]), ft_atof(params[3]));
	loader->vertices_count++;
	return (true);
}

bool	parse_normal(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
	{
		ft_putstr_fd("minirt: Wrong Normal format on line ", STDERR_FILENO);
		ft_putnbr_fd(*line_nb, STDERR_FILENO);
		ft_putendl_fd(" (ignored).", STDERR_FILENO);
		return (false);
	}
	if (!loader->normals || loader->normals_count == loader->normals_max)
	{
		loader->normals_max *= 2;
		loader->normals = ft_realloc(loader->normals,
				loader->normals_max * sizeof(t_point));
	}
	loader->normals[loader->normals_count] = new_point(ft_atof(params[1]),
			ft_atof(params[2]), ft_atof(params[3]));
	loader->normals_count++;
	return (true);
}

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	fill_indices(char **params, int *vert_i, int *norm_i, int *p_len)
{
	char	**face_info;
	int		i;
	int		f_len;

	i = -1;
	while (++i < *p_len)
	{
		face_info = ft_split(params[i + 1], '/');
		f_len = ft_matrix_len(face_info);
		if (f_len >= 1)
			vert_i[i] = ft_atoi(face_info[0]);
		if (f_len == 2)
			norm_i[i] = ft_atoi(face_info[1]);
		else if (f_len > 2)
			norm_i[i] = ft_atoi(face_info[2]);
		else
			norm_i[i] = 0;
		free(face_info);
	}
}

void	fan_triangulation(t_obj_loader *loader, int *vert_i, int *norm_i, int *p_len)
{
	int	i;

	(void)norm_i;
	if (*p_len >= 3)
	{
		i = 0;
		while (++i < *p_len - 1)
		{
			loader->triangles[loader->tri_count] = new_triangle(
					loader->vertices[vert_i[0] - 1],
					loader->vertices[vert_i[i] - 1],
					loader->vertices[vert_i[i + 1] - 1]);
			if (loader->current_g)
				add_child(loader->current_g,
					&loader->triangles[loader->tri_count]);
			else
				add_child(&loader->default_group,
					&loader->triangles[loader->tri_count]);
			loader->tri_count++;
		}
	}
}

bool	parse_triangle(t_obj_loader *loader, char **params, int *line_nb)
{
	int		*vert_i;
	int		*norm_i;
	int		p_len;

	if (!params[1] || !params[2] || !params[3])
	{
		ft_putstr_fd("minirt: Wrong Face format on line ", STDERR_FILENO);
		ft_putnbr_fd(*line_nb, STDERR_FILENO);
		ft_putendl_fd(" (ignored).", STDERR_FILENO);
		return (false);
	}
	p_len = ft_matrix_len(params) - 1;
	vert_i = malloc(p_len * sizeof(int));
	norm_i = malloc(p_len * sizeof(int));
	if (!vert_i || !norm_i)
	{
		ft_putstr_fd("minirt: Memory allocation error on line ",
			STDERR_FILENO);
		ft_putnbr_fd(*line_nb, STDERR_FILENO);
		ft_putendl_fd(" (Fatal error exiting).", STDERR_FILENO);
		exit(1);
	}
	fill_indices(params, vert_i, norm_i, &p_len);
	if (!loader->triangles || loader->tri_count == loader->tri_max)
	{
		loader->tri_max += p_len;
		loader->triangles = ft_realloc(loader->triangles,
				loader->tri_max * sizeof(t_point));
	}
	fan_triangulation(loader, vert_i, norm_i, &p_len);
	free(vert_i);
	free(norm_i);
	return (true);
}

bool	parse_group(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1])
	{
		ft_putstr_fd("minirt: Wrong Group format on line ", STDERR_FILENO);
		ft_putnbr_fd(*line_nb, STDERR_FILENO);
		ft_putendl_fd(" (ignored).", STDERR_FILENO);
		return (false);
	}
	if (!loader->groups || loader->g_count == loader->g_max)
	{
		loader->g_max *= 2;
		loader->groups = ft_realloc(loader->groups,
				loader->g_max * sizeof(t_shape));
	}
	loader->groups[loader->g_count] = new_group();
	loader->current_g = &loader->groups[loader->g_count];
	add_child(&loader->default_group, loader->current_g);
	loader->g_count++;
	return (true);
}

bool	parse_line(t_obj_loader *loader, char **params, int *line_nb)
{
	int	type_size;

	if (!params[0])
		return (false);
	type_size = ft_strlen(params[0]) + 1;
	if (ft_strncmp(params[0], "v", type_size) == 0)
		return (parse_vertice(loader, params, line_nb));
	if (ft_strncmp(params[0], "vn", type_size) == 0)
		return (parse_normal(loader, params, line_nb));
	if (ft_strncmp(params[0], "f", type_size) == 0)
		return (parse_triangle(loader, params, line_nb));
	if (ft_strncmp(params[0], "g", type_size) == 0)
		return (parse_group(loader, params, line_nb));
	return (false);
}

bool	parse_obj_file(t_obj_loader *loader, char *filename)
{
	int		fd;
	int		line_nb;
	char	*line;
	char	**params;

	line_nb = 0;
	if (!open_obj_file(filename, &fd))
		return (false);
	loader->default_group = new_group();
	line = get_next_line(fd);
	while (line)
	{
		params = ft_subsplit(line, " \n");
		if (!parse_line(loader, params, &line_nb))
			loader->ignored_lines++;
		line_nb++;
		free(line);
		free_array(params);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (true);
}

bool	obj_to_group(t_shape *g, t_obj_loader *loader)
{
	int	i;

	i = 0;
	while (i < loader->g_count)
	{
		add_child(g, &loader->groups[i]);
		i++;
	}
	return (true);
}
