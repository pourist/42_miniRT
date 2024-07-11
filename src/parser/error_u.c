/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppour-ba <ppour-ba@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:44:18 by ppour-ba          #+#    #+#             */
/*   Updated: 2024/07/02 17:44:38 by ppour-ba         ###   ########.fr       */
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
