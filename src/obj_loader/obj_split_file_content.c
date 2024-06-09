#include "obj_loader.h"

bool	split_file_in_lines(char **file_content, char ***lines, char ****tokens,
			int *nb_lines)
{
	*lines = ft_split(*file_content, '\n');
	if (!*lines)
		return (perror("minirt: ft_split"), false);
	free(*file_content);
	*file_content = NULL;
	*nb_lines = ft_matrix_len(*lines);
	*tokens = (char ***)malloc(sizeof(char **) * (*nb_lines + 1));
	if (!*tokens)
		return (perror("minirt: malloc"), false);
	(*tokens)[*nb_lines] = NULL;
	return (true);
}

void	*split_lines_in_tokens(void *data)
{
	t_thread_data	*td;
	int				line_nb;

	td = (t_thread_data *)data;
	line_nb = td->start - 1;
	while (++line_nb < td->end)
	{
		td->loader->tokens[line_nb]
			= ft_subsplit(td->loader->lines[line_nb], " \n");
		if (!td->loader->tokens[line_nb])
			return (NULL);
	}
	return (data);
}
