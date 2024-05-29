#include "parser.h"

void    make_ambient(char **rgb, double ratio, t_world *world)
{
    double  r;
    double  g;
    double  b;

    r = (ft_atof(rgb[0]) / 255) * ratio;
    g = (ft_atof(rgb[1]) / 255) * ratio;
    b = (ft_atof(rgb[2]) / 255) * ratio;
    world->ambient = new_color(r, g, b);
}

int init_ambient(char **line, t_world *world)
{
    double  ratio;
    char    **rgb;

    if (ft_strarr_len(line) != 3)
        return (free_print_error(world, "Error\nIncorrect ambient lighting elements."));
    if (!is_valid_number(line[1]))
        return (free_print_error(world, "Error\nInvalid ambient lighting ratio."));
    ratio = ft_atof(line[1]);
    if (ratio < 0 || ratio > 1)
        return(free_print_error(world, "Error\nAmbient lighting ratio out of range."));
    rgb = ft_subsplit(line[2], ",\n");
    if (ft_strarr_len(rgb) != 3 || !str_valid_numbers(rgb) || !rgb[2][0])
    {
        free_s(rgb);
        return (free_print_error(world, "Error\nRGB elements count incorrect or invalid numbers."));
    }
    if (!is_inrange(ft_atoi(rgb[0]), 0 , 255) || !is_inrange(ft_atoi(rgb[1]), 0 , 255) || !is_inrange(ft_atoi(rgb[2]), 0 , 255))
    {
        free_s(rgb);
        return (free_print_error(world, "Error\nRGB values out of range."));
    }
    make_ambient(rgb, ft_atof(line[1]),world);
    free_s(rgb);
    return (0);
}