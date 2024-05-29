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
    free_s(rgb);
}

int triplets(char **triple, double min, double max, int line)
{
    if (ft_strarr_len(triple) != 3 || !str_valid_numbers(triple))
    {
        free_s(triple);
        return (print_error("Error\nRGB elements count incorrect or invalid numbers."));
    }
    if (!are_in_range(triple, min, max))
        return (free_s(triple), print_error("Error\nRGB values out of range."));
    if (line > -12)
        return (0);
    return (0);
}

int solo(char *number, double min, double max, int line)
{
    double ratio;

   if (!is_valid_number(number))
        return (print_error("Error\nInvalid ambient lighting ratio."));
    ratio = ft_atof(number);
    if (!is_in_range(ratio, min, max))
        return(print_error("Error\nAmbient lighting ratio out of range."));
    if (line > -12)
        return (0);
    return (0);
}

// int solo_file_error(t_world *world, t_line_parse_env *parse, char *text)
// {
//     printf("Error\nLine %d: %s %s.\n", parse->line_number, text);
//     free_world(world);
//     return (1);
// }

int file_error(t_world *world, t_line_parse_env *parse, char *text)
{
    printf("Error\nLine %d: %s.\n", parse->line_number, text);
    free_world(world);
    return (1);
}

int init_ambient(t_line_parse_env *env, t_world *world)
{
    char **rgb;

    rgb = ft_subsplit(env->line[2], ",\n");
    if (ft_strarr_len(env->line) != 3)
        return (file_error(world, env, ERR_INC_AMB));
    if (solo(env->line[1], 0, 1, env->line_number))
        return (free_world(world), 1);
    if (triplets(rgb, 0, 255, env->line_number))
        return (free_world(world), 1);
    make_ambient(rgb, ft_atof(env->line[1]), world);
    return (0);
}
