/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:17:36 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:17:37 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	eq_dbl(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

double	ft_max(double a, double b, double c)
{
	double	max;

	max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return (max);
}

double	ft_min(double a, double b, double c)
{
	double	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

void	ft_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
