/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:44:18 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/17 16:28:20 by ppour-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	file_error(t_line_parse_env *parse, char *text)
{
	printf("Error\nLine %d: %s\n", parse->line_number, text);
	return (1);
}

int	file_error_line(int line, char *text)
{
	printf("Error\nLine %d: %s\n", line, text);
	return (1);
}

char	*find_error_6(int type)
{
	if (type == E_TRIPPLE)
		return (TRIPPLE);
	else if (type == E_TRIPPLE_I)
		return (TRIPPLE_I);
	else if (type == E_TRIPPLE_R)
		return (TRIPPLE_R);
	else if (type == E_DOUBLE_I)
		return (DOUBLE_I);
	else if (type == E_DOUBLE_R)
		return (DOUBLE_R);
	else if (type == SCALE)
		return (SCALE_COUNT_M);
	else if (type == SCALE_INVALID)
		return (SCALE_INVALID_M);
	else if (type == SCALE_RANGE)
		return (SCALE_RANGE_M);
	else
		return (NULL);
}
