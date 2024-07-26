/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:18:11 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/26 18:37:37 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "groups.h"

t_world	*new_world(t_world *world)
{
	world->xs = NULL;
	world->objs_count = 0;
	world->objs = NULL;
	world->objs_inside_count = 0;
	world->objs_inside = NULL;
	world->objs_ext_count = 0;
	world->lights_count = 0;
	world->lights = NULL;
	new_color(0.1, 0.1, 0.1, &world->ambient);
	world->remaining_recursion = MAX_RECURSION;
	world->pattern = NULL;
	world->bvh_groups = NULL;
	return (world);
}
