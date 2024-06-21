#include "obj_loader.h"

static bool	allocate_loader_arrays2(t_obj_loader *loader)
{
	if (loader->uv_max > 0)
	{
		loader->uvs = (t_uv *)malloc(loader->uv_max * sizeof(t_uv));
		if (!loader->uvs)
			return (perror("minirt: malloc"), false);
	}
	if (loader->mtl_max > 0)
	{
		loader->mtl_loader = (t_mtl_loader *)malloc(loader->mtl_max
				* sizeof(t_mtl_loader));
		if (!loader->mtl_loader)
			return (perror("minirt: malloc"), false);
	}
	return (true);
}

static bool	allocate_loader_arrays(t_obj_loader *loader)
{
	if (!loader->v_max || !loader->t_max)
		return (perror("minirt: obj_loader: invalid max values"), false);
	loader->vertices = (t_point *)malloc(loader->v_max * sizeof(t_point));
	if (!loader->vertices)
		return (perror("minirt: malloc"), false);
	loader->triangles = (t_shape *)malloc(loader->t_max * sizeof(t_shape));
	if (!loader->triangles)
		return (perror("minirt: malloc"), false);
	if (loader->n_max > 0)
	{
		loader->normals = (t_vector *)malloc(loader->n_max * sizeof(t_vector));
		if (!loader->normals)
			return (perror("minirt: malloc"), false);
	}
	if (loader->gp_max > 0)
	{
		loader->groups = (t_shape *)malloc(loader->gp_max * sizeof(t_shape));
		if (!loader->groups)
			return (perror("minirt: malloc"), false);
	}
	return (allocate_loader_arrays2(loader));
}

static bool	read_and_set_tokens(t_obj_loader *loader)
{
	t_threads_setup	tsetup; 
	pthread_t		*threads;
	t_thread_data	*tdata; 
	char			*file_content;

	file_content = NULL;
	if (!read_file_to_memory(loader->filename, &file_content, true))
		return (free(file_content), destroy_mutex(loader), false);
	if (!split_file_in_lines(&file_content, &loader->lines, &loader->tokens,
			&tsetup.nb_iters))
		return (free(file_content), destroy_mutex(loader), false);
	if (!set_threads_data(loader, &threads, &tdata, &tsetup))
		return (destroy_mutex(loader), free_loader(loader), false);
	if (!exec_threads_for(split_lines_in_tokens, threads, tdata,
			&tsetup.nb_threads))
		return (free_loader(loader), destroy_mutex(loader), false);
	if (!exec_threads_for(set_max_values, threads, tdata, &tsetup.nb_threads))
		return (free_loader(loader), destroy_mutex(loader), false);
	if (!allocate_loader_arrays(loader))
		return (free_loader(loader), free_loader_last(loader),
			destroy_mutex(loader), false);
	if (!load_mtl_files(loader, &tsetup.nb_iters))
		return (free_loader(loader), free_loader_last(loader),
			destroy_mutex(loader), false);
	return (destroy_mutex(loader), true);
}

static bool	create_object(t_obj_loader *loader)
{
	int	i;

	i = -1;
	while (loader->tokens[++i])
	{
		if (!obj_parse_line(loader, loader->tokens[i], i + 1))
		{
			free_loader(loader);
			free_loader_last(loader);
			return (false);
		}
	}
	free_loader(loader);
	return (true);
}

bool	parse_obj_file(t_obj_loader *loader, char const *filename)
{
	if (!loader || !filename || !loader->default_group)
	{
		ft_putendl_fd("minirt: obj_loader: invalid arguments", STDERR_FILENO);
		return (false);
	}
	loader->filename = filename;
	if (!read_and_set_tokens(loader))
		return (false);
	if (!create_object(loader))
		return (false);
	return (true);
}
