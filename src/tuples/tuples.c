/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:01:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/04/18 23:54:38 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

t_tuple	tuple(double x, double y, double z, double w)
{
	return ((t_tuple){x, y, z, w});
}

t_tuple	point(double x, double y, double z)
{
	return (tuple(x, y, z, 1.0));
}

t_tuple vector(double x, double y, double z)
{
	return (tuple(x, y, z, 0.0));
}
