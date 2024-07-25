/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_max_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:11:06 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:11:09 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_loader.h"

static void	read_face(t_obj_loader *loader, char **params, int *len)
{
	*len = ft_matrix_len(params) - 1;
	if (*len < 3)
		return ;
	pthread_mutex_lock(&loader->t_mutex);
	if (*len > 3)
		loader->t_max += *len - 2;
	else
		loader->t_max++;
	pthread_mutex_unlock(&loader->t_mutex);
}

static void	read_line2(t_obj_loader *loader, char **params, int *len,
		int *line_nb)
{
	if (ft_strncmp(params[0], "g", *len) == 0)
	{
		pthread_mutex_lock(&loader->gp_mutex);
		loader->gp_max++;
		pthread_mutex_unlock(&loader->gp_mutex);
	}
	else if (ft_strncmp(params[0], "vt", *len) == 0)
	{
		pthread_mutex_lock(&loader->uv_mutex);
		loader->uv_max++;
		pthread_mutex_unlock(&loader->uv_mutex);
	}
	else if (ft_strncmp(params[0], "mtllib", *len) == 0)
	{
		pthread_mutex_lock(&loader->mtl_mutex);
		loader->mtl_max++;
		pthread_mutex_unlock(&loader->mtl_mutex);
	}
	else
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
	}
}

static void	read_line(t_obj_loader *loader, char **params, int line_nb)
{
	int	len;

	if (params[0])
	{
		len = ft_strlen(params[0]) + 1;
		if (ft_strncmp(params[0], "v", len) == 0)
		{
			pthread_mutex_lock(&loader->v_mutex);
			loader->v_max++;
			pthread_mutex_unlock(&loader->v_mutex);
		}
		else if (ft_strncmp(params[0], "vn", len) == 0)
		{
			pthread_mutex_lock(&loader->n_mutex);
			loader->n_max++;
			pthread_mutex_unlock(&loader->n_mutex);
		}
		else if (ft_strncmp(params[0], "f", len) == 0)
			read_face(loader, params, &len);
		else
			read_line2(loader, params, &len, &line_nb);
		return ;
	}
	print_ignore_message(loader->filename, &line_nb);
	loader->ignored_lines++;
}

void	*set_max_values(void *data)
{
	t_thread_data	*td;
	t_obj_loader	*loader;
	int				line_nb;

	td = (t_thread_data *)data;
	if (!td || !td->data)
		return (ft_putendl_fd("minirt: set_max_values: Wrong arguments",
				STDERR_FILENO), NULL);
	loader = (t_obj_loader *)td->data;
	if (!loader->tokens || td->start < 0 || td->end < 0 || td->start >= td->end)
		return (ft_putendl_fd("minirt: set_max_values: Wrong arguments",
				STDERR_FILENO), NULL);
	line_nb = td->start - 1;
	while (++line_nb < td->end)
		read_line(loader, loader->tokens[line_nb], line_nb + 1);
	return (data);
}
