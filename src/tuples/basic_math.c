/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:47:19 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/04/19 16:35:56 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

t_tuple	add(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){
		t1.x + t2.x,
		t1.y + t2.y,
		t1.z + t2.z,
		t1.w + t2.w,
	});
}

t_tuple	subtract(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){
		t1.x - t2.x,
		t1.y - t2.y,
		t1.z - t2.z,
		t1.w - t2.w,
	});
}

t_tuple	negate(t_tuple t)
{
	return ((t_tuple){
		t.x * -1,
		t.y * -1,
		t.z * -1,
		t.w * -1,
	});
}

t_tuple	multiply(t_tuple t, double scalar)
{
	return ((t_tuple){
		t.x * scalar,
		t.y * scalar,
		t.z * scalar,
		t.w * scalar,
	});
}

t_tuple	division(t_tuple t, double scalar)
{
	return ((t_tuple){
		t.x / scalar,
		t.y / scalar,
		t.z / scalar,
		t.w / scalar,
	});
}

double	magnitude(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}
