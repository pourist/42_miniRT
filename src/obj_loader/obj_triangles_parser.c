#include "obj_loader.h"

static void	parse_face_indices(char *str, char *face_info[3])
{
	int	start;
	int	ends;
	int	i;

	start = 0;
	i = -1;
	while (str[start] && i < 3)
	{
		ends = start;
		while (str[ends] && str[ends] != '/')
			++ends;
		if (ends > start)
			face_info[++i] = ft_substr(str, start, ends - start);
		else
			++i;
		if (str[ends])
			start = ends + 1;
		else
			start = ends;
	}
}

static void	fill_indices(char **params, int *indices[3], int *p_len)
{
	char	*face_info[3];
	int		i;
	int		j;

	face_info[0] = NULL;
	face_info[1] = NULL;
	face_info[2] = NULL;
	i = -1;
	while (++i < *p_len)
	{
		parse_face_indices(params[i + 1], face_info);
		j = -1;
		while (++j < 3)
		{
			if (face_info[j])
				indices[j][i] = ft_atoi(face_info[j]) - 1;
			else
				indices[j][i] = -1;
			free(face_info[j]);
			face_info[j] = NULL;
		}
	}
}

bool	parse_triangle(t_obj_loader *loader, char **params, int *line_nb)
{
	int		*indices[3];
	int		p_len;

	p_len = ft_matrix_len(params) - 1;
	if (p_len < 3)
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	indices[0] = malloc(p_len * sizeof(int));
	indices[1] = malloc(p_len * sizeof(int));
	indices[2] = malloc(p_len * sizeof(int));
	if (!indices[0] || !indices[1] || ! indices[2])
		return (false);
	fill_indices(params, indices, &p_len);
	if (!fan_triangulation(loader, indices, &p_len))
		return (false);
	free(indices[0]);
	free(indices[1]);
	free(indices[2]);
	return (true);
}
