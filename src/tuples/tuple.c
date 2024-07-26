/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:16:35 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:16:36 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

t_tuple	new_tuple(double x, double y, double z, double w)
{
	return ((t_tuple){x, y, z, w});
}

t_point	*new_point(double x, double y, double z, t_point *p)
{
	*p = (t_point){x, y, z, 1.0};
	return (p);
}

t_vector	*new_vector(double x, double y, double z, t_vector *v)
{
	*v = (t_vector){x, y, z, 0.0};
	return (v);
}
