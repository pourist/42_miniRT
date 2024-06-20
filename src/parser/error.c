#include "parser.h"

char	*find_error_3(int type)
{
	if (type == CENT_INVALID)
		return (CENT_INVALID_M);
	else if (type == CENT_RANGE)
		return (CENT_RANGE_M);
	else if (type == NORMAL)
		return (NORMAL_M);
	else if (type == NORMAL_INVALID)
		return (NORMAL_INVALID_M);
	else if (type == NORMAL_RANGE)
		return (NORMAL_RANGE_M);
	else if (type == POINT)
		return (POINT_COUNT_M);
	else if (type == POINT_INVALID)
		return (POINT_INVALID_M);
	else if (type == POINT_RANGE)
		return (POINT_RANGE_M);
	else if (type == HEIGHT_VALID)
		return (H_INVALID);
	else if (type == HEIGHT_RANGE)
		return (H_RANGE_M);
	else
		return (NULL);
}

char	*find_error_2(int type)
{
	if (type == OR)
		return (OR_M);
	if (type == OR_INVALID)
		return (OR_INVALID_M);
	if (type == OR_RANGE)
		return (OR_RANGE_M);
	if (type == L_RATIO)
		return (L_RATIO_M);
	if (type == L_RATIO_RANGE)
		return (L_RATIO_RANGE_M);
	if (type == POS)
		return (POS_M);
	if (type == POS_INVALID)
		return (POS_INVALID_M);
	if (type == POS_RANGE)
		return (POS_RANGE_M);
	if (type == DIAM)
		return (D_INVALID);
	if (type == DIAM_RANGE)
		return (D_RANGE_M);
	if (type == CENT)
		return (CENT_M);
	return (find_error_3(type));
}

char	*find_error(int type)
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


int	file_error(t_line_parse_env *parse, char *text)
{
	printf("Error\nLine %d: %s\n", parse->line_number, text);
	return (1);
}
