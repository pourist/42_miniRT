#include "obj_loader.h"

t_obj_loader	new_obj_loader(void)
{
	t_obj_loader	loader;

	loader.ignored_lines = 0;
	loader.vertices = NULL;
	loader.v_count = 0;
	loader.v_max = 0;
	loader.normals = NULL;
	loader.n_count = 0;
	loader.n_max = 0;
	loader.triangles = NULL;
	loader.t_count = 0;
	loader.t_max = 0;
	loader.default_group = new_group();
	loader.groups = NULL;
	loader.g_count = 0;
	loader.g_max = 0;
	loader.current_g = &loader.default_group;
	return (loader);
}

void	free_loader(t_obj_loader *loader)
{
	if (!loader)
		return ;
	free(loader->vertices);
	free(loader->normals);
	free(loader->triangles);
	free(loader->groups);
}

bool	open_obj_file(char *filename, int *fd)
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
