/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:17:04 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:17:05 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	get_sign(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (**str == '+')
		(*str)++;
	return (1);
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		sign;

	result = 0.0;
	fraction = 0.1;
	sign = get_sign(&str);
	while (str && *str != '.')
	{
		if (!ft_isdigit(*str))
			return (sign * result);
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result += fraction * (*str - '0');
			fraction *= 0.1;
			str++;
		}
	}
	return (sign * result);
}
