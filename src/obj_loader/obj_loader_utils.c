#include "obj_loader.h"

bool	print_ignore_message(char const *filename, int *line_nb)
{
	ft_putstr_fd("minirt: obj files loader: ", STDERR_FILENO);
	ft_putstr_fd((char *)filename, STDERR_FILENO);
	ft_putstr_fd(": Line ", STDERR_FILENO);
	ft_putnbr_fd(*line_nb, STDERR_FILENO);
	ft_putendl_fd(" ignored.", STDERR_FILENO);
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

void	destroy_mutex(t_obj_loader *loader)
{
	if (!loader)
		return ;
	if (loader->lines)
	{
		free_matrix(loader->lines);
		loader->lines = NULL;
	}
	pthread_mutex_destroy(&loader->v_mutex);
	pthread_mutex_destroy(&loader->n_mutex);
	pthread_mutex_destroy(&loader->t_mutex);
	pthread_mutex_destroy(&loader->gp_mutex);
	pthread_mutex_destroy(&loader->ig_lines_mutex);
	pthread_mutex_destroy(&loader->mtl_mutex);
	pthread_mutex_destroy(&loader->uv_mutex);
}
