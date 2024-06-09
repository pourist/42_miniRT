#include "obj_loader.h"

static bool	allocate_loader_arrays(t_obj_loader *loader)
{
	loader->normals = (t_vector *)malloc(loader->n_max * sizeof(t_vector));
	if (!loader->normals)
		return (perror("minirt: malloc"), false);
	loader->groups = (t_shape *)malloc(loader->gp_max * sizeof(t_shape));
	if (!loader->groups)
		return (perror("minirt: malloc"), free(loader->normals), false);
	loader->vertices = (t_point *)malloc(loader->v_max * sizeof(t_point));
	if (!loader->vertices)
		return (perror("minirt: malloc"), free(loader->normals),
			free(loader->groups), false);
	loader->triangles = (t_shape *)malloc(loader->t_max * sizeof(t_shape));
	if (!loader->triangles)
		return (perror("minirt: malloc"), free(loader->normals),
			free(loader->groups), free(loader->vertices), false);
	return (true);
}

static void	free_threads_data(t_obj_loader *loader, pthread_t *threads,
			t_thread_data *thread_data)
{
	free_matrix(loader->lines);
	pthread_mutex_destroy(&loader->v_mutex);
	pthread_mutex_destroy(&loader->n_mutex);
	pthread_mutex_destroy(&loader->t_mutex);
	pthread_mutex_destroy(&loader->gp_mutex);
	pthread_mutex_destroy(&loader->ig_lines_mutex);
	free(threads);
	free(thread_data);
}

static bool	read_and_set_tokens(t_obj_loader *loader)
{
	t_threads_data	threads_data;
	pthread_t		*threads;
	t_thread_data	*thread_data;
	char			*file_content;

	if (!read_file_to_memory(loader->filename, &file_content))
		return (free(file_content), false);
	if (!split_file_in_lines(&file_content, &loader->lines, &loader->tokens,
			&threads_data.nb_lines))
		return (free(file_content), free_matrix(loader->lines), false);
	if (!set_threads_data(loader, &threads, &thread_data, &threads_data))
		return (free_matrix(loader->lines), free_3d_array(loader->tokens),
			free(threads), free(thread_data), false);
	if (!exec_threads_for(split_lines_in_tokens, threads, thread_data,
			&threads_data.threads_count))
		return (free_3d_array(loader->tokens), free_matrix(loader->lines),
			free(threads), free(thread_data), false);
	if (!exec_threads_for(set_max_values, threads, thread_data,
			&threads_data.threads_count))
		return (free_3d_array(loader->tokens), free(threads), free(thread_data),
			false);
	if (!allocate_loader_arrays(loader))
		return (free_3d_array(loader->tokens), free(threads), free(thread_data),
			false);
	return (free_threads_data(loader, threads, thread_data), true);
}

static bool	create_object(t_obj_loader *loader)
{
	int	i;

	i = -1;
	while (loader->tokens[++i])
	{
		if (!parse_line(loader, loader->tokens[i], i + 1))
		{
			free_3d_array(loader->tokens);
			free(loader->vertices);
			free(loader->normals);
			free(loader->triangles);
			free(loader->groups);
			return (false);
		}
	}
	free_3d_array(loader->tokens);
	free(loader->vertices);
	free(loader->normals);
	return (true);
}

bool	parse_obj_file(t_obj_loader *loader, char const *filename)
{
	if (!loader || !filename)
		return (false);
	loader->filename = filename;
	if (!read_and_set_tokens(loader))
		return (false);
	if (!create_object(loader))
		return (false);
	return (true);
}
