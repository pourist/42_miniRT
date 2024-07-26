/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_mapping2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:15:47 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:15:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"

double	*cube_uv_back(t_point *point, double uv[2])
{
	uv[0] = fmod(1 - point->x, 2) * 0.5; 
	if (uv[0] < 0)
		uv[0] += 0.5;
	uv[1] = fmod(point->y + 1, 2) * 0.5;
	if (uv[1] < 0)
		uv[1] += 0.5;
	return (uv);
}

double	*cube_uv_up(t_point *point, double uv[2])
{
	uv[0] = fmod(point->x + 1, 2) * 0.5; 
	if (uv[0] < 0)
		uv[0] += 0.5;
	uv[1] = fmod(1 - point->z, 2) * 0.5;
	if (uv[1] < 0)
		uv[1] += 0.5;
	return (uv);
}

double	*cube_uv_down(t_point *point, double uv[2])
{
	uv[0] = fmod(point->x + 1, 2) * 0.5;
	if (uv[0] < 0)
		uv[0] += 0.5;
	uv[1] = fmod(point->z + 1, 2) * 0.5;
	if (uv[1] < 0)
		uv[1] += 0.5;
	return (uv);
}
