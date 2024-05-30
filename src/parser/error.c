#include "parser.h"

char    *find_error_2(int type)
{
    if (type == OR)
        return (OR_M);
    if (type == OR_INVALID)
        return (OR_INVALID_M);
    if (type == OR_RANGE)
        return (OR_RANGE_M);
    return (NULL);
}

char    *find_error(int type)
{
    if (type == RATIO)
        return (RATIO_INVALID);
    else if (type == RATIO_OUT_RANGE)
        return (RATIO_RANGE);
    else if (type == RGB)
        return (RGB_LEN);
    else if (type == RGB_VALID)
        return (RGB_INVALID);
    else if (type == RGB_OUT_RANGE)
        return (RGB_RANGE);
    else if (type == FOV)
        return (FOV_M);
    else if (type == FOV_RANGE)
        return (FOV_RANGE_M);
    else if (type == POV)
        return (POV_M);
    else if (type == POV_INVALID)
        return (POV_INVALID_M);
    else if (type == POV_RANGE)
        return (POV_RANGE_M);
    else
        return (find_error_2(type));
}


int file_error(t_line_parse_env *parse, char *text)
{
    printf("Error\nLine %d: %s\n", parse->line_number, text);
    return (1);
}