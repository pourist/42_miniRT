#include "parser.h"

void    set_type(t_line_parse_env    *parse)
{
    if (parse->line[0] == NULL)
        parse->type = EMPTY_LINE;
    else if (!ft_strncmp(parse->line[0], "A", 2))
        parse->type = AMBIENT;
    else if (!ft_strncmp(parse->line[0], "C", 2))
        parse->type = CAMERA;
    else if (!ft_strncmp(parse->line[0], "L", 2))
        parse->type = LIGHT;
    else if (!ft_strncmp(parse->line[0], "sp", 2))
        parse->type = SPHERE;
    else if (!ft_strncmp(parse->line[0], "cy", 2))
        parse->type = CYLINDER;
    else if (!ft_strncmp(parse->line[0], "pl", 2))
        parse->type = PLANE;
}

int    parse_line(int fd, t_line_parse_env    *parse)
{
        parse->line_number++;
        parse->temp = get_next_line(fd);
		if (!parse->temp || parse->temp[0] == '\0')
		{
			free(parse->temp);
			return (1);
		}
		parse->line = ft_subsplit (parse->temp, " \t\n");
		free(parse->temp);
        set_type(parse);
        return (0);
}

int read_lines_init(t_world *world, int fd)
{
    t_line_parse_env    parse;

    parse.line_number = -1;
    while (1)
    {
        if(parse_line(fd, &parse))
            break;
        if (parse.type == AMBIENT && init_ambient(&parse, world))
            return (free_s(parse.line));
        free_s(parse.line);
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