#include "obj_loader.h"

static bool	parse_line(t_obj_loader *loader, char **params, int *line_nb)
{
	int	type_size;

	if (!params[0])
		return (loader->ignored_lines++, true);
	type_size = ft_strlen(params[0]) + 1;
	if (ft_strncmp(params[0], "v", type_size) == 0)
		return (parse_vertice(loader, params, line_nb));
	else if (ft_strncmp(params[0], "vn", type_size) == 0)
		return (parse_normal(loader, params, line_nb));
	else if (ft_strncmp(params[0], "f", type_size) == 0)
		return (parse_triangle(loader, params, line_nb));
	else if (ft_strncmp(params[0], "g", type_size) == 0)
		return (parse_group(loader, params, line_nb));
	else
		return (loader->ignored_lines++, true);
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

bool	parse_obj_file(t_obj_loader *loader, char *filename)
{
	int		fd;
	int		line_nb;
	char	*line;
	char	**params;

	if (!loader || !filename)
		return (false);
	if (!set_max_values(loader, filename) || !open_obj_file(filename, &fd))
		return (false);
	line_nb = 1;
	line = get_next_line(fd);
	while (line)
	{
		params = ft_subsplit(line, " \n");
		if (!parse_line(loader, params, &line_nb))
			return (free(line), free_array(params), close(fd),
				free_loader(loader), false);
		free(line);
		free_array(params);
		line = get_next_line(fd);
		line_nb++;
	}
	return (free(line), close(fd), true);
}
