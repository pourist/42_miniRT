#include "parser.h"

int read_lines_init(t_world *world, int fd)
{
    char    *temp_line;
    char    **line;

    while (1)
    {
        temp_line = get_next_line(fd);
		if (!temp_line || temp_line[0] == '\0')
		{
			free(temp_line);
			break ;
		}
		line = ft_subsplit (temp_line, " \t\n");
		free(temp_line);
        if (line[0] && !ft_strncmp(line[0], "A", 2) && init_ambient(line, world))
            return (free_s(line));
        if (L)

        C
        free_s(line);
    }
    return (0);
}

int     init_world(t_world *world, t_e_counts *count)
{
    int objs_count;

    objs_count = count->cylinder + count->sphere + count->plane;
    world->objs_count = objs_count;
    world->lights_count = count->light;
    world->objs = (t_shape *)malloc(sizeof(t_shape) * (objs_count));
    if (!world->objs)
        return (print_error("Error\nMemory allocation failed."));
    world->lights = (t_light *)malloc(sizeof(t_light) * (world->lights_count));
    if (!world->lights)
        return (free(world->objs), print_error("Error\nMemory allocation failed."));
    if (read_lines_init(world, count->fd))
        return (1);
    return (0);
}

int     init_minirt(t_mini_rt *minirt, t_e_counts *count)
{
    minirt->world = new_world();
    if (init_world(&(minirt->world), count))
        return (1);
    return (0);
}