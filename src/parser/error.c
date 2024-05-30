#include "parser.h"

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
    return (NULL);
}


int file_error(t_line_parse_env *parse, char *text)
{
    printf("Error\nLine %d: %s\n", parse->line_number, text);
    return (1);
}