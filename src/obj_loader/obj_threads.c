#include "obj_loader.h"

bool	set_threads_data(t_obj_loader *loader, pthread_t **threads,
			t_thread_data **t_data, t_threads_data *data)
{
	long		nprocs;
	int			i;

	nprocs = sysconf(_SC_NPROCESSORS_ONLN) * THREADS_FRACTION;
	if (nprocs < 1)
		nprocs = 1;
	data->threads_count = (int)nprocs;
	*threads = (pthread_t *)malloc(sizeof(pthread_t) * nprocs);
	if (!*threads)
		return (perror("minirt: malloc"), false);
	*t_data = (t_thread_data *)malloc(sizeof(t_thread_data) * nprocs);
	if (!*t_data)
		return (perror("minirt: malloc"), false);
	data->lines_per_thread = data->nb_lines / data->threads_count;
	i = -1;
	while (++i < data->threads_count)
	{
		(*t_data)[i].loader = loader;
		(*t_data)[i].start = i * data->lines_per_thread;
		if (i == data->threads_count - 1)
			(*t_data)[i].end = data->nb_lines;
		else
			(*t_data)[i].end = (i + 1) * data->lines_per_thread;
	}
	return (true);
}

bool	exec_threads_for(t_thread_fn thread_fn, pthread_t *threads,
			t_thread_data *thread_data, int *threads_count)
{
	int		i;
	void	*status;

	i = -1;
	while (++i < *threads_count)
	{
		if (pthread_create(&threads[i], NULL,
				thread_fn, &thread_data[i]) != 0)
			return (perror("minirt: pthread_create"), false);
	}
	i = -1;
	while (++i < *threads_count)
	{
		pthread_join(threads[i], &status);
		if (!status)
			return (perror("minirt: exec_threads_for"), false);
	}
	return (true);
}
