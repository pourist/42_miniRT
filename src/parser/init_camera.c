#include "parser.h"

// C -50.0,0,20 0,0,1 70

double  degrees_to_radian(double degrees)
{
    return (degrees * (M_PI / 180.0));
}




//     to = new_point(-50.0, 0, 21); // to create this point you have to add the view_point to the orientation vector => add(from, new_vector(0,0,1))
//         dont forget to use new_vector to make a correct add.
//     up = new_vector(0, 1, 0); // by default.
//     set_transform_camera(camera, view_transform(&from, &to, &up));
// }

void    make_camera(t_camera *camera, double fov, char **pov)
{
    t_point from;
    // t_point to;
    // t_vector up;

    *camera = new_camera(WIDTH, HEIGHT, degrees_to_radian(fov));
    from = new_point(ft_atof(pov[0]), ft_atof(pov[1]), ft_atof(pov[2]));

    // up = new_vector(0, 1, 0);
}

int init_camera(t_line_parse_env *env, t_camera *camera)
{
    char    **pov;
    char    **orientation;

    if (ft_strarr_len(env->line) != 4)
        return (file_error(env, ERR_INC_CAM));
    env->error_type = FOV;
    if (solo((env->line[3]), 0, 180, env))
        return (1);
    env->error_type = POV;
    pov = ft_subsplit(env->line[1], ",\n");
    if (triplets(pov, (double)INT_MIN, (double)INT_MAX, env))
        return (1);
    env->error_type = OR;
    orientation = ft_subsplit(env->line[2], ",\n");
    if (triplets(orientation, -1, 1, env))
        return (free_s(pov), 1);
    make_camera(camera, ft_atof(env->line[3]), pov);
    free_s(pov);
    free_s(orientation);
    return (0);
}